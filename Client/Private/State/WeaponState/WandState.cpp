#include "stdafx.h"
#include "WandState.h"

#include "Export_System.h"

#include "NonWeaponState.h"
#include "SwordState.h"

CWandState::CWandState()
{
}

CWandState::~CWandState()
{
}

HRESULT CWandState::Ready_State(CCharacter* pcharacter)
{
	pcharacter->Add_Weapon(WEAPONTYPE::WAND);

	return S_OK;
}

CWeaponState* CWandState::Update_State(CCharacter* pcharacter, const float& fTimeDelta)
{

	CWeaponState* weapon = CWeaponState::Update_State(pcharacter, fTimeDelta);
	if (dynamic_cast<CWandState*>(weapon))
	{
		return nullptr;
	}

	return weapon;
}

CWandState* CWandState::Create(CCharacter* pcharacter)
{
	CWandState* pInstance = new CWandState();

	if (FAILED(pInstance->Ready_State(pcharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWandState::Free()
{

	CWeaponState::Free();
}
