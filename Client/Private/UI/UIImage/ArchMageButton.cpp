#include "stdafx.h"
#include "..\Header\ArchMageButton.h"

#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "ArchMage.h"
#include "AreaMgr.h"

CArchMageButton::CArchMageButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CArchMageButton::CArchMageButton(const CArchMageButton& rhs)
	: CUIImage(rhs)
{
}

CArchMageButton::~CArchMageButton()
{
}

HRESULT CArchMageButton::Ready_GameObject(const _int& iPirce)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_MageButton"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	m_iPrice = iPirce;

	return S_OK;
}

_int CArchMageButton::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_bCollCheck) {
		if (!CSquardMgr::GetInstance()->Is_Commender_Buy_It(WEAPONTYPE::WAND)) {
			if (CResourceMgr::GetInstance()->Get_Money() - m_iPrice >= 0) {
				CResourceMgr::GetInstance()->Purchase(m_iPrice);
				//CObjCreationMgr::GetInstance()->Create_SquardCommander<CArchMage>(_vec3(70.f, 5.f, 0.f), _vec3(50.f, 3.f, 50.f));
				//CObjCreationMgr::GetInstance()->Create<CArchMage>(OBJECTTYPE::PLAYER, _vec3(70.f, 5.f, 0.f), _vec3(50.f, 3.f, 50.f));

				CResourceMgr::GetInstance()->Purchase(m_iPrice);

				_int	iPlayerBeaconIndex = CAreaMgr::GetInstance()->Get_AllyOuterAreaIndex();
				_vec3	vSpawnPos = CAreaMgr::GetInstance()->Get_BeaconPos(iPlayerBeaconIndex);
				vSpawnPos.z += 10.f;
				_vec3	vTargetPos = vSpawnPos;
				vTargetPos.z += 10.f;
				CObjCreationMgr::GetInstance()->Create_SquardCommander<CArchMage>(vSpawnPos, vTargetPos);


				m_iTextureNum = 1;
				m_fCount = 0.f;
				m_bCollCheck = false;
			}
		}
	}

	if (m_iTextureNum == 1) {
		if (m_fCount > 0.1f) {
			m_iTextureNum = 0;
			m_fCount = 0.f;
		}
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CArchMageButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CArchMageButton::Render_GameObject()
{
	CUIImage::Render_GameObject();
}

HRESULT CArchMageButton::Add_Component()
{

	return S_OK;
}

CArchMageButton* CArchMageButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _int& iPirce)
{
	CArchMageButton* pInstance = new CArchMageButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(iPirce))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CArchMageButton::Free()
{
	CUIImage::Free();
}
