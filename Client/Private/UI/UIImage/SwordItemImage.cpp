#include "stdafx.h"
#include "..\Header\SwordItemImage.h"

#include "Export_Utility.h"

#include "SquardMgr.h"

CSwordItemImage::CSwordItemImage(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CSwordItemImage::CSwordItemImage(const CSwordItemImage& rhs)
	: CUIImage(rhs)
{
}

CSwordItemImage::~CSwordItemImage()
{
}

HRESULT CSwordItemImage::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_Item"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	return S_OK;
}

_int CSwordItemImage::Update_GameObject(const _float& fTimeDelta)
{
	return CUIImage::Update_GameObject(fTimeDelta);
}

void CSwordItemImage::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CSwordItemImage::Render_GameObject()
{
	if (!CSquardMgr::GetInstance()->Is_Squard_Exist()) {
		if (CSquardMgr::GetInstance()->Get_SelectedSquard() != SQUARD_ID_END) {
			CUIImage::Render_GameObject();
		}
	}

	
}

HRESULT CSwordItemImage::Add_Component()
{

	return S_OK;
}

CSwordItemImage* CSwordItemImage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSwordItemImage* pInstance = new CSwordItemImage(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSwordItemImage::Free()
{
	CUIImage::Free();
}
