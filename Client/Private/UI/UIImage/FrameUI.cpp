#include "stdafx.h"
#include "..\Header\FrameUI.h"

#include "Export_Utility.h"
#include "Export_System.h"

#include "SquardMgr.h"

CFrameUI::CFrameUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CFrameUI::CFrameUI(const CFrameUI& rhs)
	: CUIImage(rhs)
{
}

CFrameUI::~CFrameUI()
{
}


HRESULT CFrameUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_FrameUI"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	return S_OK;
}

_int CFrameUI::Update_GameObject(const _float& fTimeDelta)
{

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CFrameUI::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

CFrameUI* CFrameUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFrameUI* pInstance = new CFrameUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("FrameUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFrameUI::Render_GameObject()
{
	if (!CSquardMgr::GetInstance()->Is_Squard_Exist()) {
		if (CSquardMgr::GetInstance()->Get_SelectedSquard() != SQUARD_ID_END) {
			CUIImage::Render_GameObject();
		}
	}
}

void CFrameUI::Free()
{
	CUIImage::Free();
}

HRESULT CFrameUI::Add_Component()
{

	return S_OK;
}


