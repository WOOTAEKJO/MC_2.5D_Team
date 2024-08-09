#include "stdafx.h"
#include "..\Header\BuildUIState.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "ManagementUI.h"
#include "ControlUI.h"

#include "NPCUIState.h"
#include "ItemUIState.h"
#include "ETCUIState.h"

#include "StoreCreateButton.h"

#include "CurrentModeMgr.h"

CBuildUIState::CBuildUIState()
{
}

CBuildUIState::~CBuildUIState()
{
}

HRESULT CBuildUIState::Ready_State(CUI* pUI)
{
	pUI->Set_TextureNum(2);
	dynamic_cast<CControlUI*>(pUI)->Set_StateType(CControlUI::STATETYPE::TYPE_3);
	dynamic_cast<CControlUI*>(pUI)->Create_ItemImage();

	return S_OK;
}

CUIState* CBuildUIState::Update_State(CUI* pUI, const float& fTimeDelta)
{
	//if (CCurrentModeMgr::GetInstance()->Get_Current_State_ID() == CURRENTSTATEID::UIMODE)
	{
		dynamic_cast<CControlUI*>(pUI)->Pick_UI();

		if (Engine::Key_Down(DIK_UP)) {
			dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
			return CItemUIState::Create(pUI);
		}

		if (Engine::Key_Down(DIK_DOWN)) {
			dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
			return CETCUIState::Create(pUI);
		}
	}

	return nullptr;
}

CBuildUIState* CBuildUIState::Create(CUI* pUI)
{
	CBuildUIState* pInstance = new CBuildUIState();

	if (FAILED(pInstance->Ready_State(pUI))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBuildUIState::Free(CUI* pUI)
{
	
}
