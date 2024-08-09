#include "stdafx.h"
#include "..\Header\LAButton.h"

#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "StoreUI.h"

CLAButton::CLAButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CLAButton::CLAButton(const CLAButton& rhs)
	: CUIImage(rhs)
{
}

CLAButton::~CLAButton()
{
}

HRESULT CLAButton::Ready_GameObject(CUI* pUI)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_LABUTTON"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;
	m_pUI = pUI;
	return S_OK;
}

_int CLAButton::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_bCollCheck) {

		static_cast<CStoreUI*>(m_pUI)->Set_ChangeType(true);

		m_iTextureNum = 1;
		m_fCount = 0.f;
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

void CLAButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CLAButton::Render_GameObject()
{
	CUIImage::Render_GameObject();
}

HRESULT CLAButton::Add_Component()
{

	return S_OK;
}

CLAButton* CLAButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI)
{
	CLAButton* pInstance = new CLAButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pUI))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLAButton::Free()
{
	CUIImage::Free();
}
