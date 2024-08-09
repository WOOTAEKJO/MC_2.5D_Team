#include "stdafx.h"
#include "..\Header\StoreUIState2.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "ControlUI.h"
#include "ManagementUI.h"

#include "ObjCreationMgr.h"

#include "StoreUIState1.h"
#include "StoreUI.h"

CStoreUIState2::CStoreUIState2()
{
}

CStoreUIState2::~CStoreUIState2()
{
}

HRESULT CStoreUIState2::Ready_State(CUI* pUI)
{
	pUI->Set_TextureNum(0);
	dynamic_cast<CControlUI*>(pUI)->Set_StateType(CControlUI::STATETYPE::TYPE_2);
	dynamic_cast<CControlUI*>(pUI)->Create_ItemImage();

	return S_OK;
}

CUIState* CStoreUIState2::Update_State(CUI* pUI, const float& fTimeDelta)
{

	dynamic_cast<CControlUI*>(pUI)->Pick_UI();

	if (dynamic_cast<CStoreUI*>(pUI)->Get_ChangeType()) {
		dynamic_cast<CStoreUI*>(pUI)->Set_ChangeType(false);
		dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
		return CStoreUIState1::Create(pUI);
	}

	return nullptr;
}

CStoreUIState2* CStoreUIState2::Create(CUI* pUI)
{
	CStoreUIState2* pInstance = new CStoreUIState2();

	if (FAILED(pInstance->Ready_State(pUI))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CStoreUIState2::Free(CUI* pUI)
{
	
}
