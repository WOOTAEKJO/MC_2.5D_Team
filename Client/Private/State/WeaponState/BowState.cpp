#include "stdafx.h"
#include "..\Header\BowState.h"

#include "Export_System.h"

#include "NonWeaponState.h"
#include "SwordState.h"

CBowState::CBowState()
{
}

CBowState::~CBowState()
{
}

HRESULT CBowState::Ready_State(CCharacter* pcharacter)
{
	pcharacter->Add_Weapon(WEAPONTYPE::BOW);

	return S_OK;
}

CWeaponState* CBowState::Update_State(CCharacter* pcharacter, const float& fTimeDelta)
{

	CWeaponState* weapon = CWeaponState::Update_State(pcharacter, fTimeDelta);
	if (dynamic_cast<CBowState*>(weapon))
	{
		return nullptr;
	}
	return weapon;

}

CBowState* CBowState::Create(CCharacter* pcharacter)
{
	CBowState* pInstance = new CBowState();

	if (FAILED(pInstance->Ready_State(pcharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBowState::Free()
{

	CWeaponState::Free();
}
