#include "stdafx.h"
#include "..\Header\SwordState.h"

#include "Export_System.h"

#include "NonWeaponState.h"
#include "BowState.h"

CSwordState::CSwordState()
{
}

CSwordState::~CSwordState()
{
}

HRESULT CSwordState::Ready_State(CCharacter* pcharacter)
{
	pcharacter->Add_Weapon(WEAPONTYPE::SWORD);

	return S_OK;
}

CWeaponState* CSwordState::Update_State(CCharacter* pcharacter, const float& fTimeDelta)
{

	CWeaponState* weapon = CWeaponState::Update_State(pcharacter, fTimeDelta);
	if (dynamic_cast<CSwordState*>(weapon))
	{
		return nullptr;
	}
	return weapon;

}

CSwordState* CSwordState::Create(CCharacter* pcharacter)
{
	CSwordState* pInstance = new CSwordState();

	if (FAILED(pInstance->Ready_State(pcharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSwordState::Free()
{
	
	CWeaponState::Free();
}
