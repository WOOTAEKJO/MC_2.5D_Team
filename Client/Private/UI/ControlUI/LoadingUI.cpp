#include "stdafx.h"
#include "..\Header\LoadingUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"
#include "AreaMgr.h"

#include "IconBoxUI.h"
#include "IconUI.h"
#include "ProgressBarUI.h"

CLoadingUI::CLoadingUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
}

CLoadingUI::CLoadingUI(const CLoadingUI& rhs)
	: CControlUI(rhs)
{
}

CLoadingUI::~CLoadingUI()
{
}


HRESULT CLoadingUI::Ready_GameObject()
{
	//FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BossBar"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);
	FAILED_CHECK_RETURN(CLoadingUI::Create_ItemImage(), E_FAIL);

	//m_vTransform->Set_Pos(_vec3(10.f, 265.f, 1.f));
	//m_vTransform->Set_Scale(_vec3(270.f, 15.f, 1.f));

	m_iTextureNum = 0;


	//m_pUIState = CLoadingUIState1::Create(this);
	//m_eUI_RenderType = UIORDER::ALWAYSUI;
	Set_UI_RenderType(UIORDER::ALWAYSUI);
	return S_OK;
}

_int CLoadingUI::Update_GameObject(const _float& fTimeDelta)
{
	
	return CControlUI::Update_GameObject(fTimeDelta);
}

void CLoadingUI::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}

HRESULT CLoadingUI::Create_ItemImage()
{

	_vec3 vBarScale = { 30.f,6.f,1.f };
	_vec3 vBoxScale = { 17.f,17.f,1.f };
	_vec3 vIconScale = { 15.f,15.f,1.f };

	CGameObject* pGameObject = nullptr;

	

	return S_OK;
}

CLoadingUI* CLoadingUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLoadingUI* pInstance = new CLoadingUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ItemBox Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CLoadingUI::Render_GameObject()
{
	//CControlUI::Render_GameObject();

	if (!m_bHide) {
		if (!m_vecItemImage.empty()) {
			for (auto& iter : m_vecItemImage) {
				iter->Render_GameObject();
			}
		}
	}

}

void CLoadingUI::Free()
{
	CControlUI::Free();
}

HRESULT CLoadingUI::Add_Component()
{
	return S_OK;
}
