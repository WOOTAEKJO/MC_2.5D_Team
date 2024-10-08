#include "stdafx.h"
#include "..\Header\FourthSquadButton.h"

#include "Export_System.h"
#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "StoreUI.h"

CFourthSquadButton::CFourthSquadButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CFourthSquadButton::CFourthSquadButton(const CFourthSquadButton& rhs)
	: CUIImage(rhs)
{
}

CFourthSquadButton::~CFourthSquadButton()
{
}

HRESULT CFourthSquadButton::Ready_GameObject(CUI* pUI)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_NonButton"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;
	m_pUI = pUI;
	return S_OK;
}

_int CFourthSquadButton::Update_GameObject(const _float& fTimeDelta)
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

void CFourthSquadButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CFourthSquadButton::Render_GameObject()
{
	CUIImage::Render_GameObject();
	if (!m_bHide) {
		_vec3 vPos = *m_vTransform->Get_Pos();
		_vec3 vScale = *m_vTransform->Get_Scale();
		//_vec2 vPos2 = { vPos.x + (vScale.x * 1.2f), vPos.y + (vScale.y * 0.7f) };
		_vec2 vPos2 = { 463.f, 143.f };
		_tchar srTest[100] = {};
		swprintf_s(srTest, L"4�д�");
		Engine::Render_Font(L"Font_ButtonUI", srTest, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	}
}

HRESULT CFourthSquadButton::Add_Component()
{

	return S_OK;
}

CFourthSquadButton* CFourthSquadButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI)
{
	CFourthSquadButton* pInstance = new CFourthSquadButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pUI))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFourthSquadButton::Free()
{
	CUIImage::Free();
}
