#include "stdafx.h"
#include "..\Header\ManagementUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"

#include "NPCUIState.h"

#include "Heart.h"
#include "StoreCreateButton.h"
#include "BuildCreateButton.h"

CManagementUI::CManagementUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
}

CManagementUI::CManagementUI(const CManagementUI& rhs)
	: CControlUI(rhs)
{
}

CManagementUI::~CManagementUI()
{
}


HRESULT CManagementUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_ManagerUIImage"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);

	

	//m_iTextureNum = 0;

	//FAILED_CHECK_RETURN(CManagementUI::Create_ItemImage(), E_FAIL);

	m_pUIState = CNPCUIState::Create(this);

	return S_OK;
}

_int CManagementUI::Update_GameObject(const _float& fTimeDelta)
{
	CUIState* pUIState = m_pUIState->Update_State(this, fTimeDelta);
	if (pUIState != nullptr)
	{
		m_pUIState->Free(this);
		Safe_Delete(m_pUIState);
		m_pUIState = pUIState;
	}

	

	return CControlUI::Update_GameObject(fTimeDelta);
}

void CManagementUI::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}

HRESULT CManagementUI::Create_ItemImage()
{
	_vec3 vScale = { 16.f,16.f,1.f };
	_vec3 vFrameScale = { 32.f,32.f,1.f };

	CGameObject* pGameObject = nullptr;

	if (m_eStateType == STATETYPE::TYPE_1) {
		pGameObject = CHeart::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(_vec3(0.f, 0.f, 1.f));
		pGameObject->Get_Transform()->Set_Scale(_vec3(8.f, 8.f, 1.f));
		m_vecItemImage.push_back(pGameObject);

		pGameObject = CHeart::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(_vec3(100.f, 100.f, 1.f));
		pGameObject->Get_Transform()->Set_Scale(_vec3(8.f, 8.f, 1.f));
		m_vecItemImage.push_back(pGameObject);
	}
	else if (m_eStateType == STATETYPE::TYPE_2) {

	}
	else if (m_eStateType == STATETYPE::TYPE_3) {
		/*pGameObject = CStoreCreateButton::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(_vec3(20.f, 130.f, 1.f));
		pGameObject->Get_Transform()->Set_Scale(_vec3(256.f, 32.f, 1.f));
		m_vecItemImage.push_back(pGameObject);*/
	}
	else if (m_eStateType == STATETYPE::TYPE_4) {

	}

	return S_OK;
}

CManagementUI* CManagementUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CManagementUI* pInstance = new CManagementUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ItemBox Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CManagementUI::Render_GameObject()
{
	CControlUI::Render_GameObject();
}

void CManagementUI::Free()
{
	CControlUI::Free();
}

HRESULT CManagementUI::Add_Component()
{
	return S_OK;
}
