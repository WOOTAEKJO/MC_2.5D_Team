#include "stdafx.h"
#include "..\Header\Emerald.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

CEmerald::CEmerald(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CEmerald::CEmerald(const CEmerald& rhs)
	: CUIImage(rhs)
{
}

CEmerald::~CEmerald()
{
}

HRESULT CEmerald::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_Emerald"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	return S_OK;
}

_int CEmerald::Update_GameObject(const _float& fTimeDelta)
{
	

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CEmerald::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CEmerald::Render_GameObject()
{

	CUIImage::Render_GameObject();

}

HRESULT CEmerald::Add_Component()
{

	return S_OK;
}

CEmerald* CEmerald::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEmerald* pInstance = new CEmerald(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEmerald::Free()
{
	CUIImage::Free();
}
