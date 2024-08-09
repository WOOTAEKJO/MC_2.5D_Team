#include "stdafx.h"
#include "..\Header\NonWeaponState.h"

#include "Export_System.h"

#include "SwordState.h"
#include "BowState.h"

CNonWeaponState::CNonWeaponState()
{
}

CNonWeaponState::~CNonWeaponState()
{
}

HRESULT CNonWeaponState::Ready_State(CCharacter* pcharacter)
{
	pcharacter->Set_WeaponType(WEAPONTYPE::WEAPON_END);
	return S_OK;
}

CWeaponState* CNonWeaponState::Update_State(CCharacter* pcharacter, const float& fTimeDelta)
{
	CWeaponState* weapon = CWeaponState::Update_State(pcharacter, fTimeDelta);
	if (dynamic_cast<CNonWeaponState*>(weapon)) 
	{
		return nullptr;
	}
	return weapon;
	
}

CNonWeaponState* CNonWeaponState::Create(CCharacter* pcharacter)
{
	CNonWeaponState* pInstance = new CNonWeaponState();

	if (FAILED(pInstance->Ready_State(pcharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("NonWS Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNonWeaponState::Free()
{
	CWeaponState::Free();
}
