#include "stdafx.h"
#include "..\Header\WeaponState.h"
#include "Export_System.h"

#include "NonWeaponState.h"
#include "SwordState.h"
#include "BowState.h"
#include "WandState.h"

#include "CurrentModeMgr.h"

CWeaponState::CWeaponState()
{
}

CWeaponState::~CWeaponState()
{
}

HRESULT CWeaponState::Ready_State(CCharacter* pcharacter)
{
	return S_OK;
}

CWeaponState* CWeaponState::Update_State(CCharacter* pcharacter, const float& fTimeDelta)
{
	if (CCurrentModeMgr::GetInstance()->Get_Current_State_ID() == CURRENTSTATEID::NORMAL) 
	{
		if (Engine::Key_Pressing(DIK_1)) {
			pcharacter->Delete_Weapon();
			return CNonWeaponState::Create(pcharacter);
		}
		if (Engine::Key_Pressing(DIK_2)) {
			pcharacter->Delete_Weapon();
			return CSwordState::Create(pcharacter);
		}
		if (Engine::Key_Pressing(DIK_3)) {
			pcharacter->Delete_Weapon();
			return CBowState::Create(pcharacter);
		}
		if (Engine::Key_Pressing(DIK_4)) {
			pcharacter->Delete_Weapon();
			return CWandState::Create(pcharacter);
		}
	}
	

	return nullptr;
}

void CWeaponState::Free()
{
}
