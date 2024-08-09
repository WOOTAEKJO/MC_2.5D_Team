#include "stdafx.h"
#include "..\Header\ShooterButton.h"

#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "Shooter.h"
#include "AreaMgr.h"

CShooterButton::CShooterButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CShooterButton::CShooterButton(const CShooterButton& rhs)
	: CUIImage(rhs)
{
}

CShooterButton::~CShooterButton()
{
}

HRESULT CShooterButton::Ready_GameObject(const _int& iPirce)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BowButton"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	m_iPrice = iPirce;

	return S_OK;
}

_int CShooterButton::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_bCollCheck) {
		if (!CSquardMgr::GetInstance()->Is_Commender_Buy_It(WEAPONTYPE::BOW)) {
			if (CResourceMgr::GetInstance()->Get_Money() - m_iPrice >= 0) {
				CResourceMgr::GetInstance()->Purchase(m_iPrice);
				//CObjCreationMgr::GetInstance()->Create_SquardCommander<CShooter>(_vec3(70.f, 5.f, 0.f), _vec3(50.f, 3.f, 50.f));
				
				CResourceMgr::GetInstance()->Purchase(m_iPrice);
				_int	iPlayerBeaconIndex = CAreaMgr::GetInstance()->Get_AllyOuterAreaIndex();
				_vec3	vSpawnPos = CAreaMgr::GetInstance()->Get_BeaconPos(iPlayerBeaconIndex);
				vSpawnPos.z += 10.f;
				_vec3	vTargetPos = vSpawnPos;
				vTargetPos.z += 10.f;
				CObjCreationMgr::GetInstance()->Create_SquardCommander<CShooter>(vSpawnPos, vTargetPos);

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

void CShooterButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CShooterButton::Render_GameObject()
{
	CUIImage::Render_GameObject();
}

HRESULT CShooterButton::Add_Component()
{

	return S_OK;
}

CShooterButton* CShooterButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _int& iPirce)
{
	CShooterButton* pInstance = new CShooterButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(iPirce))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShooterButton::Free()
{
	CUIImage::Free();
}
