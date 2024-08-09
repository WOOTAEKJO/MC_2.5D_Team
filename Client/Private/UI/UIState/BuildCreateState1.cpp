#include "stdafx.h"
#include "..\Header\BuildCreateState1.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "SquardMgr.h"

#include "ControlUI.h"
#include "ManagementUI.h"

#include "ObjCreationMgr.h"

#include "ItemBox.h"

#include "BuildCreateState2.h"

CBuildCreateState1::CBuildCreateState1()
{
}

CBuildCreateState1::~CBuildCreateState1()
{
}

HRESULT CBuildCreateState1::Ready_State(CUI* pUI)
{
	pUI->Set_TextureNum(0);
	dynamic_cast<CControlUI*>(pUI)->Set_StateType(CControlUI::STATETYPE::TYPE_1);
	dynamic_cast<CControlUI*>(pUI)->Create_ItemImage();

	return S_OK;
}

CUIState* CBuildCreateState1::Update_State(CUI* pUI, const float& fTimeDelta)
{

	dynamic_cast<CControlUI*>(pUI)->Pick_UI();

	if (dynamic_cast<CControlUI*>(pUI)->Get_ChangeType()) {
		dynamic_cast<CControlUI*>(pUI)->Set_ChangeType(false);
		dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
		return CBuildCreateState2::Create(pUI);
	}

	return nullptr;
}

CBuildCreateState1* CBuildCreateState1::Create(CUI* pUI)
{
	CBuildCreateState1* pInstance = new CBuildCreateState1();

	if (FAILED(pInstance->Ready_State(pUI))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBuildCreateState1::Free(CUI* pUI)
{

}
