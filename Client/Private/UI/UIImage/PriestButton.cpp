#include "stdafx.h"
#include "..\Header\PriestButton.h"

#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "PriestSoldier.h"
#include "HighPriest.h"

#include "StoreUI.h"

CPriestButton::CPriestButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CPriestButton::CPriestButton(const CPriestButton& rhs)
	: CUIImage(rhs)
{
}

CPriestButton::~CPriestButton()
{
}

HRESULT CPriestButton::Ready_GameObject(const _int& iPirce)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_PriestButton"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	m_iPrice = iPirce;

	return S_OK;
}

_int CPriestButton::Update_GameObject(const _float& fTimeDelta)
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

						CObjCreationMgr::GetInstance()->Create_Player<CPriestSoldier>(vPos, vPicPos, eType);

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

void CPriestButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CPriestButton::Render_GameObject()
{
	CUIImage::Render_GameObject();
}

HRESULT CPriestButton::Add_Component()
{

	return S_OK;
}

CPriestButton* CPriestButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _int& iPirce)
{
	CPriestButton* pInstance = new CPriestButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(iPirce))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPriestButton::Free()
{
	CUIImage::Free();
}
