#include "stdafx.h"
#include "..\Header\Heart.h"

#include "Export_Utility.h"

#include "SquardMgr.h"

CHeart::CHeart(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CHeart::CHeart(const CHeart& rhs)
	: CUIImage(rhs)
{
}

CHeart::~CHeart()
{
}


HRESULT CHeart::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_Heart"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);
	
	m_iTextureNum = 0;

	return S_OK;
}

_int CHeart::Update_GameObject(const _float& fTimeDelta)
{
	if (m_bCollCheck) {
		if (m_iTextureNum == 0) {
			m_iTextureNum = 1;
		}
		else if (m_iTextureNum == 1) {
			m_iTextureNum = 0;
		}
		m_bCollCheck = false;
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CHeart::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}


CHeart* CHeart::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHeart* pInstance = new CHeart(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
			Safe_Release(pInstance);

			MSG_BOX("Heart Create Failed");
			return nullptr;
	}

	return pInstance;
}


void CHeart::Render_GameObject()
{
	if (!CSquardMgr::GetInstance()->Is_Squard_Exist()) {
		if (CSquardMgr::GetInstance()->Get_SelectedSquard() != SQUARD_ID_END) {
			CUIImage::Render_GameObject();
		}
	}
}

void CHeart::Free()
{
	CUIImage::Free();
}

HRESULT CHeart::Add_Component()
{

	return S_OK;
}
