#include "stdafx.h"
#include "..\Header\BuildLAButton.h"

#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "HighPriest.h"

#include "StoreUI.h"

CBuildLAButton::CBuildLAButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CBuildLAButton::CBuildLAButton(const CBuildLAButton& rhs)
	: CUIImage(rhs)
{
}

CBuildLAButton::~CBuildLAButton()
{
}

HRESULT CBuildLAButton::Ready_GameObject(CUI* pUI)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_LABUTTON"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;
	m_pUI = pUI;
	return S_OK;
}

_int CBuildLAButton::Update_GameObject(const _float& fTimeDelta)
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

void CBuildLAButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CBuildLAButton::Render_GameObject()
{
	CUIImage::Render_GameObject();
}

HRESULT CBuildLAButton::Add_Component()
{

	return S_OK;
}

CBuildLAButton* CBuildLAButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI)
{
	CBuildLAButton* pInstance = new CBuildLAButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pUI))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBuildLAButton::Free()
{
	CUIImage::Free();
}
