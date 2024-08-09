#include "stdafx.h"
#include "..\Header\ProgressUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"
#include "AreaMgr.h"

#include "IconBoxUI.h"
#include "IconUI.h"
#include "ProgressBarUI.h"

CProgressUI::CProgressUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
	ZeroMemory(m_pBox, sizeof(m_pBox));
	ZeroMemory(m_pBar, sizeof(m_pBar));
	ZeroMemory(m_pIcon, sizeof(m_pIcon));
}

CProgressUI::CProgressUI(const CProgressUI& rhs)
	: CControlUI(rhs)
{
}

CProgressUI::~CProgressUI()
{
}


HRESULT CProgressUI::Ready_GameObject()
{
	//FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BossBar"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);
	FAILED_CHECK_RETURN(CProgressUI::Create_ItemImage(), E_FAIL);

	//m_vTransform->Set_Pos(_vec3(10.f, 265.f, 1.f));
	//m_vTransform->Set_Scale(_vec3(270.f, 15.f, 1.f));

	m_iTextureNum = 0;


	//m_pUIState = CProgressUIState1::Create(this);
	//m_eUI_RenderType = UIORDER::ALWAYSUI;
	Set_UI_RenderType(UIORDER::ALWAYSUI);
	return S_OK;
}

_int CProgressUI::Update_GameObject(const _float& fTimeDelta)
{
	/*CUIState* pUIState = m_pUIState->Update_State(this, fTimeDelta);
	if (pUIState != nullptr)
	{
		m_pUIState->Free(this);
		Safe_Delete(m_pUIState);
		m_pUIState = pUIState;
	}*/
	/*if (m_vecItemImage.empty()) {
		FAILED_CHECK_RETURN(CProgressUI::Create_ItemImage(), E_FAIL);
	}*/

	Cur_Progress();

	return CControlUI::Update_GameObject(fTimeDelta);
}

void CProgressUI::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}

void CProgressUI::Cur_Progress()
{
	_int iNum = CAreaMgr::GetInstance()->Get_AllyOuterAreaIndex();

	for (_ushort i = 0; i < 4; ++i) {
		if (i != 0) {
			m_pBar[i - 1]->Set_TextureNum(1);
		}
		m_pBox[i]->Set_TextureNum(1);
		m_pIcon[i]->Set_TextureNum(1);
	}

	for (_ushort i = 0; i <= iNum; ++i) 
	{	
		if (i != 0) {
			m_pBar[i-1]->Set_TextureNum(0);
		}
		m_pBox[i]->Set_TextureNum(0);
		m_pIcon[i]->Set_TextureNum(0);
	}

}

HRESULT CProgressUI::Create_ItemImage()
{
	
	_vec3 vBarScale = {30.f,6.f,1.f};
	_vec3 vBoxScale = { 17.f,17.f,1.f };
	_vec3 vIconScale = { 15.f,15.f,1.f };

	CGameObject* pGameObject = nullptr;

	for (_int i = 0; i < 3; i++) {
		pGameObject = m_pBar[i] = CProgressBarUI::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(_vec3(-84.f+(i*84.f),250.f,1.f));
		pGameObject->Get_Transform()->Set_Scale(vBarScale);
		m_vecItemImage.push_back(pGameObject);
	}
	
	for (_int i = 0; i < 4;i++) {

		pGameObject = m_pBox[i] =CIconBoxUI::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(_vec3(-124.f + (i*84), 250.f, 1.f));
		pGameObject->Get_Transform()->Set_Scale(vBoxScale);
		m_vecItemImage.push_back(pGameObject);
	}

	for (_int i = 0; i < 4; i++) {

		pGameObject = m_pIcon[i] = CIconUI::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(_vec3(-124.f + (i * 84), 250.f, 1.f));
		pGameObject->Get_Transform()->Set_Scale(vIconScale);
		m_vecItemImage.push_back(pGameObject);
	}

	return S_OK;
}

CProgressUI* CProgressUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CProgressUI* pInstance = new CProgressUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ItemBox Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CProgressUI::Render_GameObject()
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

void CProgressUI::Free()
{
	CControlUI::Free();
}

HRESULT CProgressUI::Add_Component()
{
	return S_OK;
}
