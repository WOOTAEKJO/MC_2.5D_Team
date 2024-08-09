#include "stdafx.h"
#include "..\Header\BuildCreateState2.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "SquardMgr.h"

#include "ControlUI.h"
#include "ManagementUI.h"

#include "ObjCreationMgr.h"

#include "BuildCreateState1.h"

#include "ItemBox.h"

CBuildCreateState2::CBuildCreateState2()
{
}

CBuildCreateState2::~CBuildCreateState2()
{
}

HRESULT CBuildCreateState2::Ready_State(CUI* pUI)
{
	pUI->Set_TextureNum(0);
	dynamic_cast<CControlUI*>(pUI)->Set_StateType(CControlUI::STATETYPE::TYPE_2);
	dynamic_cast<CControlUI*>(pUI)->Create_ItemImage();

	return S_OK;
}

CUIState* CBuildCreateState2::Update_State(CUI* pUI, const float& fTimeDelta)
{

	dynamic_cast<CControlUI*>(pUI)->Pick_UI();

	if (dynamic_cast<CControlUI*>(pUI)->Get_ChangeType()) {
		dynamic_cast<CControlUI*>(pUI)->Set_ChangeType(false);
		dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
		return CBuildCreateState1::Create(pUI);
	}

	return nullptr;
}

CBuildCreateState2* CBuildCreateState2::Create(CUI* pUI)
{
	CBuildCreateState2* pInstance = new CBuildCreateState2();

	if (FAILED(pInstance->Ready_State(pUI))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBuildCreateState2::Free(CUI* pUI)
{

}
