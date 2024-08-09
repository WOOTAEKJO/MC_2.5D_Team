#include "stdafx.h"
#include "..\Header\SwordButton.h"

#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "ResourceMgr.h"
#include "SquardMgr.h"

#include "SSoldier.h"
#include "SwordMaster.h"

#include "StoreUI.h"

CSwordButton::CSwordButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CSwordButton::CSwordButton(const CSwordButton& rhs)
	: CUIImage(rhs)
{
}

CSwordButton::~CSwordButton()
{
}

HRESULT CSwordButton::Ready_GameObject(const _int& iPirce)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_SwordButton"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	m_iPrice = iPirce;

	return S_OK;
}

_int CSwordButton::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_bCollCheck) {
		
		
		//CObjCreationMgr::GetInstance()->Create_Character_Behine_Player<CSSoldier>(OBJECTTYPE::PLAYER);
		//CObjCreationMgr::GetInstance()->Create<CSSoldier>(OBJECTTYPE::PLAYER, _vec3(50.f, 5.f, 0.f), _vec3(50.f, 3.f, 50.f));
		if (CResourceMgr::GetInstance()->Get_Money() - m_iPrice >= 0) {
			if (m_pUI != nullptr && !m_pUI->Get_Dead()) {
				SQUARD_ID eType = static_cast<CStoreUI*>(m_pUI)->Get_SquadType();
				if (CSquardMgr::GetInstance()->Is_Squard_Full_Check(eType)) {
					CCharacter* pCommander = CSquardMgr::GetInstance()->Get_SquardCommander(eType);
					if (pCommander != nullptr) {

						CResourceMgr::GetInstance()->Purchase(m_iPrice);
						_vec3 vPos = *pCommander->Get_Transform()->Get_Pos();
						_vec3 vPicPos = pCommander->Get_PickPos();

						CObjCreationMgr::GetInstance()->Create_Player<CSSoldier>(vPos, vPicPos, eType);

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

void CSwordButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CSwordButton::Render_GameObject()
{
	CUIImage::Render_GameObject();
}

HRESULT CSwordButton::Add_Component()
{

	return S_OK;
}

CSwordButton* CSwordButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _int& iPirce)
{
	CSwordButton* pInstance = new CSwordButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(iPirce))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSwordButton::Free()
{
	CUIImage::Free();
}
