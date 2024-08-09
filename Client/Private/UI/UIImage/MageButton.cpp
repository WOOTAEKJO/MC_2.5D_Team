#include "stdafx.h"
#include "..\Header\MageButton.h"

#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "MageSoldier.h"
#include "ArchMage.h"

#include "StoreUI.h"

CMageButton::CMageButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CMageButton::CMageButton(const CMageButton& rhs)
	: CUIImage(rhs)
{
}

CMageButton::~CMageButton()
{
}

HRESULT CMageButton::Ready_GameObject(const _int& iPirce)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_MageButton"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	m_iPrice = iPirce;

	return S_OK;
}

_int CMageButton::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_bCollCheck) {
		if (CResourceMgr::GetInstance()->Get_Money() - m_iPrice >= 0) {
			if (m_pUI != nullptr && !m_pUI->Get_Dead()) {
				SQUARD_ID eType = static_cast<CStoreUI*>(m_pUI)->Get_SquadType();
				if (CSquardMgr::GetInstance()->Is_Squard_Full_Check(eType)) {
					CCharacter* pCommander = CSquardMgr::GetInstance()->Get_SquardCommander(eType);
					if (pCommander != nullptr) {

						CResourceMgr::GetInstance()->Purchase(m_iPrice);
						_vec3 vPos = *pCommander->Get_Transform()->Get_Pos();
						_vec3 vPicPos = pCommander->Get_PickPos();

						CObjCreationMgr::GetInstance()->Create_Player<CMageSoldier>(vPos, vPicPos, eType);

						m_iTextureNum = 1;
						m_fCount = 0.f;
					}

				}
			}
		}
		m_bCollCheck = false;
	}

	if (m_iTextureNum == 1) {
		if (m_fCount > 0.1f) {
			m_iTextureNum = 0;
			m_fCount = 0.f;
		}
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CMageButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CMageButton::Render_GameObject()
{
	CUIImage::Render_GameObject();
}

HRESULT CMageButton::Add_Component()
{

	return S_OK;
}

CMageButton* CMageButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _int& iPirce)
{
	CMageButton* pInstance = new CMageButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(iPirce))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMageButton::Free()
{
	CUIImage::Free();
}
