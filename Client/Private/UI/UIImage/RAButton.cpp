#include "stdafx.h"
#include "..\Header\RAButton.h"

#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "HighPriest.h"

#include "StoreUI.h"

CRAButton::CRAButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CRAButton::CRAButton(const CRAButton& rhs)
	: CUIImage(rhs)
{
}

CRAButton::~CRAButton()
{
}

HRESULT CRAButton::Ready_GameObject(CUI* pUI)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_RABUTTON"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;
	m_pUI = pUI;
	return S_OK;
}

_int CRAButton::Update_GameObject(const _float& fTimeDelta)
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

void CRAButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CRAButton::Render_GameObject()
{
	CUIImage::Render_GameObject();
}

HRESULT CRAButton::Add_Component()
{

	return S_OK;
}

CRAButton* CRAButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI)
{
	CRAButton* pInstance = new CRAButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pUI))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRAButton::Free()
{
	CUIImage::Free();
}
