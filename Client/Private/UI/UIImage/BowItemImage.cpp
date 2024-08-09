#include "stdafx.h"
#include "..\Header\BowItemImage.h"

#include "Export_Utility.h"

#include "SquardMgr.h"

CBowItemImage::CBowItemImage(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CBowItemImage::CBowItemImage(const CBowItemImage& rhs)
	: CUIImage(rhs)
{
}

CBowItemImage::~CBowItemImage()
{
}

HRESULT CBowItemImage::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_Item"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 1;

	return S_OK;
}

_int CBowItemImage::Update_GameObject(const _float& fTimeDelta)
{
	return CUIImage::Update_GameObject(fTimeDelta);
}

void CBowItemImage::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CBowItemImage::Render_GameObject()
{
	if (!CSquardMgr::GetInstance()->Is_Squard_Exist()) {
		if (CSquardMgr::GetInstance()->Get_SelectedSquard() != SQUARD_ID_END) {
			CUIImage::Render_GameObject();
		}
	}
}

HRESULT CBowItemImage::Add_Component()
{

	return S_OK;
}

CBowItemImage* CBowItemImage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBowItemImage* pInstance = new CBowItemImage(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBowItemImage::Free()
{
	CUIImage::Free();
}
