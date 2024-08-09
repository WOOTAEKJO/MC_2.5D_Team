#include "stdafx.h"
#include "..\Header\BossStateUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "BossNameBox.h"

CBossStateUI::CBossStateUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
	//D3DXMatrixIdentity(&m_matWorld);
}

CBossStateUI::CBossStateUI(const CBossStateUI& rhs)
	: CUIImage(rhs)
{
}

CBossStateUI::~CBossStateUI()
{
}

HRESULT CBossStateUI::Ready_GameObject(CUI* pUI)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BossStateUI"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	//m_vTransform->Set_Scale(100.f, 10.f, 20.f);

	m_iTextureNum = 0;
	m_pUI = pUI;
	NULL_CHECK_RETURN(m_pUI,E_FAIL);

	return S_OK;
}

_int CBossStateUI::Update_GameObject(const _float& fTimeDelta)
{
	//Add_Count(fTimeDelta);

	if (static_cast<CBossNameBox*>(m_pUI)->Is_Change_State())
	{
		m_iTextureNum = 1;
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CBossStateUI::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CBossStateUI::Render_GameObject()
{

	CUIImage::Render_GameObject();
}

HRESULT CBossStateUI::Add_Component()
{

	return S_OK;
}

CBossStateUI* CBossStateUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI)
{
	CBossStateUI* pInstance = new CBossStateUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pUI))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBossStateUI::Free()
{
	CUIImage::Free();
}
