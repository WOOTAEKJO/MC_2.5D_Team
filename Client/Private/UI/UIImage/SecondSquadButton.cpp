#include "stdafx.h"
#include "..\Header\SecondSquadButton.h"

#include "Export_System.h"
#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "StoreUI.h"

CSecondSquadButton::CSecondSquadButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CSecondSquadButton::CSecondSquadButton(const CSecondSquadButton& rhs)
	: CUIImage(rhs)
{
}

CSecondSquadButton::~CSecondSquadButton()
{
}

HRESULT CSecondSquadButton::Ready_GameObject(CUI* pUI)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_NonButton"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;
	m_pUI = pUI;
	return S_OK;
}

_int CSecondSquadButton::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_bCollCheck) {

		if (m_pUI != nullptr && !m_pUI->Get_Dead()) {
			static_cast<CStoreUI*>(m_pUI)->Set_SquadType(m_eSquadID);

			m_iTextureNum = 1;
			m_fCount = 0.f;
			m_bCollCheck = false;
		}
	}

	if (m_iTextureNum == 1) {
		/*if (m_fCount > 0.1f) {
			m_iTextureNum = 0;
			m_fCount = 0.f;
		}*/
		if (m_pUI != nullptr && !m_pUI->Get_Dead()) {
			if (static_cast<CStoreUI*>(m_pUI)->Get_SquadType() != m_eSquadID) {
				m_iTextureNum = 0;
			}
		}
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CSecondSquadButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CSecondSquadButton::Render_GameObject()
{
	CUIImage::Render_GameObject();
	if (!m_bHide) {
		_vec3 vPos = *m_vTransform->Get_Pos();
		_vec3 vScale = *m_vTransform->Get_Scale();
		//_vec2 vPos2 = { vPos.x + (vScale.x * 1.2f), vPos.y + (vScale.y * 0.7f) };
		_vec2 vPos2 = { 263.f, 143.f };
		_tchar srTest[100] = {};
		swprintf_s(srTest, L"2ºÐ´ë");
		Engine::Render_Font(L"Font_ButtonUI", srTest, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	}
}

HRESULT CSecondSquadButton::Add_Component()
{

	return S_OK;
}

CSecondSquadButton* CSecondSquadButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI)
{
	CSecondSquadButton* pInstance = new CSecondSquadButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pUI))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSecondSquadButton::Free()
{
	CUIImage::Free();
}
