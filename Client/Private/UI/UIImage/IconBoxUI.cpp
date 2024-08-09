#include "stdafx.h"
#include "..\Header\IconBoxUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

CIconBoxUI::CIconBoxUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CIconBoxUI::CIconBoxUI(const CIconBoxUI& rhs)
	: CUIImage(rhs)
{
}

CIconBoxUI::~CIconBoxUI()
{
}

HRESULT CIconBoxUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_IconBox"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 1;

	m_vTransform->m_vAngle.z = D3DXToRadian(45.f);

	return S_OK;
}

_int CIconBoxUI::Update_GameObject(const _float& fTimeDelta)
{


	return CUIImage::Update_GameObject(fTimeDelta);
}

void CIconBoxUI::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CIconBoxUI::Render_GameObject()
{

	CUIImage::Render_GameObject();

}

HRESULT CIconBoxUI::Add_Component()
{

	return S_OK;
}

CIconBoxUI* CIconBoxUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIconBoxUI* pInstance = new CIconBoxUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CIconBoxUI::Free()
{
	CUIImage::Free();
}
