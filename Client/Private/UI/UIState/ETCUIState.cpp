#include "stdafx.h"
#include "..\Header\ETCUIState.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "ControlUI.h"
#include "ManagementUI.h"

#include "NPCUIState.h"
#include "ItemUIState.h"
#include "BuildUIState.h"

CETCUIState::CETCUIState()
{
}

CETCUIState::~CETCUIState()
{
}

HRESULT CETCUIState::Ready_State(CUI* pUI)
{
	pUI->Set_TextureNum(3);
	dynamic_cast<CControlUI*>(pUI)->Set_StateType(CControlUI::STATETYPE::TYPE_4);
	dynamic_cast<CControlUI*>(pUI)->Create_ItemImage();

	return S_OK;
}

CUIState* CETCUIState::Update_State(CUI* pUI, const float& fTimeDelta)
{
	if (Engine::Key_Down(DIK_UP)) {
		dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
		return CBuildUIState::Create(pUI);
	}

	return nullptr;
}

CETCUIState* CETCUIState::Create(CUI* pUI)
{
	CETCUIState* pInstance = new CETCUIState();

	if (FAILED(pInstance->Ready_State(pUI))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CETCUIState::Free(CUI* pUI)
{
	//dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
}
