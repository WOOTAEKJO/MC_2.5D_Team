#include "stdafx.h"
#include "..\Header\IconUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

CIconUI::CIconUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CIconUI::CIconUI(const CIconUI& rhs)
	: CUIImage(rhs)
{
}

CIconUI::~CIconUI()
{
}

HRESULT CIconUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_Icon"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 1;

	//m_vTransform->m_vAngle.z = D3DXToRadian(45.f);

	return S_OK;
}

_int CIconUI::Update_GameObject(const _float& fTimeDelta)
{


	return CUIImage::Update_GameObject(fTimeDelta);
}

void CIconUI::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CIconUI::Render_GameObject()
{

	CUIImage::Render_GameObject();

}

HRESULT CIconUI::Add_Component()
{

	return S_OK;
}

CIconUI* CIconUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CIconUI* pInstance = new CIconUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CIconUI::Free()
{
	CUIImage::Free();
}
