#include "stdafx.h"
#include "..\Header\NPCUIState.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "ControlUI.h"
#include "ManagementUI.h"

#include "ItemUIState.h"
#include "BuildUIState.h"
#include "ETCUIState.h"

#include "ObjCreationMgr.h"
#include "Heart.h"

CNPCUIState::CNPCUIState()
{
}

CNPCUIState::~CNPCUIState()
{
}

HRESULT CNPCUIState::Ready_State(CUI* pUI)
{
	pUI->Set_TextureNum(0);
	dynamic_cast<CControlUI*>(pUI)->Set_StateType(CControlUI::STATETYPE::TYPE_1);
	dynamic_cast<CControlUI*>(pUI)->Create_ItemImage();

	return S_OK;
}

CUIState* CNPCUIState::Update_State(CUI* pUI, const float& fTimeDelta)
{

	dynamic_cast<CControlUI*>(pUI)->Pick_UI();

	if (Engine::Key_Down(DIK_DOWN)) {
		dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
		return CItemUIState::Create(pUI);
	}

	return nullptr;
}

CNPCUIState* CNPCUIState::Create(CUI* pUI)
{
	CNPCUIState* pInstance = new CNPCUIState();

	if (FAILED(pInstance->Ready_State(pUI))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNPCUIState::Free(CUI* pUI)
{
	//dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
}
