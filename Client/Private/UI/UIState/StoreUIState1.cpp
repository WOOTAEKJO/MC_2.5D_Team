#include "stdafx.h"
#include "..\Header\StoreUIState1.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "ControlUI.h"
#include "ManagementUI.h"

#include "ObjCreationMgr.h"

#include "StoreUIState2.h"
#include "StoreUI.h"

CStoreUIState1::CStoreUIState1()
{
}

CStoreUIState1::~CStoreUIState1()
{
}

HRESULT CStoreUIState1::Ready_State(CUI* pUI)
{
	pUI->Set_TextureNum(0);
	dynamic_cast<CControlUI*>(pUI)->Set_StateType(CControlUI::STATETYPE::TYPE_1);
	dynamic_cast<CControlUI*>(pUI)->Create_ItemImage();

	return S_OK;
}

CUIState* CStoreUIState1::Update_State(CUI* pUI, const float& fTimeDelta)
{

	dynamic_cast<CControlUI*>(pUI)->Pick_UI();

	if (dynamic_cast<CStoreUI*>(pUI)->Get_ChangeType()) {
		dynamic_cast<CStoreUI*>(pUI)->Set_ChangeType(false);
		dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
		return CStoreUIState2::Create(pUI);
	}

	return nullptr;
}

CStoreUIState1* CStoreUIState1::Create(CUI* pUI)
{
	CStoreUIState1* pInstance = new CStoreUIState1();

	if (FAILED(pInstance->Ready_State(pUI))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CStoreUIState1::Free(CUI* pUI)
{
	
}
