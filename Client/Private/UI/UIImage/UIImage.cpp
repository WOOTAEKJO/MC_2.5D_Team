#include "stdafx.h"
#include "..\Header\UIImage.h"

#include "Export_Utility.h"

CUIImage::CUIImage(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
}

CUIImage::CUIImage(const CUIImage& rhs)
	: CUI(rhs)
{
}

CUIImage::~CUIImage()
{
}

HRESULT CUIImage::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Ready_GameObject(), E_FAIL);

	return S_OK;
}

_int CUIImage::Update_GameObject(const _float& fTimeDelta)
{
	return CUI::Update_GameObject(fTimeDelta);
}

void CUIImage::LateUpdate_GameObject()
{
	CUI::LateUpdate_GameObject();
}

void CUIImage::Render_GameObject()
{
	CUI::Render_GameObject();
}

HRESULT CUIImage::Add_Component()
{
	return S_OK;
}

void CUIImage::Free()
{
	CUI::Free();
}


