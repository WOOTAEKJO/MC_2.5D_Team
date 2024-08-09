#include "stdafx.h"
#include "..\Header\ProgressBarUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

CProgressBarUI::CProgressBarUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CProgressBarUI::CProgressBarUI(const CProgressBarUI& rhs)
	: CUIImage(rhs)
{
}

CProgressBarUI::~CProgressBarUI()
{
}

HRESULT CProgressBarUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_ProgressBar"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 1;

	//m_vTransform->m_vAngle.z = D3DXToRadian(45.f);

	return S_OK;
}

_int CProgressBarUI::Update_GameObject(const _float& fTimeDelta)
{


	return CUIImage::Update_GameObject(fTimeDelta);
}

void CProgressBarUI::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CProgressBarUI::Render_GameObject()
{

	CUIImage::Render_GameObject();

}

HRESULT CProgressBarUI::Add_Component()
{

	return S_OK;
}

CProgressBarUI* CProgressBarUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CProgressBarUI* pInstance = new CProgressBarUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CProgressBarUI::Free()
{
	CUIImage::Free();
}
