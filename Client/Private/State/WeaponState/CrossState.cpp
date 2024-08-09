#include "stdafx.h"
#include "CrossState.h"

#include "Export_System.h"

#include "NonWeaponState.h"
#include "SwordState.h"

CCrossState::CCrossState()
{
}

CCrossState::~CCrossState()
{
}

HRESULT CCrossState::Ready_State(CCharacter* pcharacter)
{
	pcharacter->Add_Weapon(WEAPONTYPE::CROSS);

	return S_OK;
}

CWeaponState* CCrossState::Update_State(CCharacter* pcharacter, const float& fTimeDelta)
{

	CWeaponState* weapon = CWeaponState::Update_State(pcharacter, fTimeDelta);
	if (dynamic_cast<CCrossState*>(weapon))
	{
		return nullptr;
	}

	return weapon;
}

CCrossState* CCrossState::Create(CCharacter* pcharacter)
{
	CCrossState* pInstance = new CCrossState();

	if (FAILED(pInstance->Ready_State(pcharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCrossState::Free()
{

	CWeaponState::Free();
}
