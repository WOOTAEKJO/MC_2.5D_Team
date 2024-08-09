#include "stdafx.h"
#include "..\Header\ItemBoxUIState.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "SquardMgr.h"

#include "ControlUI.h"
#include "ManagementUI.h"

#include "ObjCreationMgr.h"

#include "ItemBox.h"

CItemBoxUIState::CItemBoxUIState()
{
}

CItemBoxUIState::~CItemBoxUIState()
{
}

HRESULT CItemBoxUIState::Ready_State(CUI* pUI)
{
	eSquadType = CSquardMgr::GetInstance()->Get_SelectedSquard();
	if (eSquadType != SQUARD_ID_END) {
		CCharacter* pCharacter = CSquardMgr::GetInstance()->Get_SquardCommander(eSquadType);
		FAILED_CHECK_RETURN(pCharacter, E_FAIL);
		WEAPONTYPE eType = pCharacter->Get_WeaponType();
		dynamic_cast<CItemBox*>(pUI)->Set_WeaponType(eType);
		dynamic_cast<CControlUI*>(pUI)->Create_ItemImage();
	}

	return S_OK;
}

CUIState* CItemBoxUIState::Update_State(CUI* pUI, const float& fTimeDelta)
{

	if (eSquadType != CSquardMgr::GetInstance()->Get_SelectedSquard()) {
		dynamic_cast<CControlUI*>(pUI)->Delete_ItemImage();
		return CItemBoxUIState::Create(pUI);
	}

	return nullptr;
}

CItemBoxUIState* CItemBoxUIState::Create(CUI* pUI)
{
	CItemBoxUIState* pInstance = new CItemBoxUIState();

	if (FAILED(pInstance->Ready_State(pUI))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CItemBoxUIState::Free(CUI* pUI)
{

}
