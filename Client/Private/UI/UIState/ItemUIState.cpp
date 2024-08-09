#include "stdafx.h"
#include "..\Header\ItemUIState.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "ManagementUI.h"

#include "NPCUIState.h"
#include "BuildUIState.h"
#include "ETCUIState.h"

CItemUIState::CItemUIState()
{
}

CItemUIState::~CItemUIState()
{
}

HRESULT CItemUIState::Ready_State(CUI* pUI)
{
	pUI->Set_TextureNum(1);
	dynamic_cast<CControlUI*>(pUI)->Set_StateType(CControlUI::STATETYPE::TYPE_2);
	dynamic_cast<CControlUI*>(pUI)->Create_ItemImage();

	return S_OK;
}

CUIState* CItemUIState::Update_State(CUI* pUI, const float& fTimeDelta)
{
	if (Engine::Key_Down(DIK_UP)) {
		dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
		return CNPCUIState::Create(pUI);
	}

	if (Engine::Key_Down(DIK_DOWN)) {
		dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
		return CBuildUIState::Create(pUI);
	}

	return nullptr;
}

CItemUIState* CItemUIState::Create(CUI* pUI)
{
	CItemUIState* pInstance = new CItemUIState();

	if (FAILED(pInstance->Ready_State(pUI))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CItemUIState::Free(CUI* pUI)
{
	//dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
}
