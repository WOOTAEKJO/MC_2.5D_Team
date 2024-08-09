#include "stdafx.h"
#include "ShieldState.h"

#include "Export_System.h"

#include "NonWeaponState.h"
#include "SwordState.h"

CShieldState::CShieldState()
{
}

CShieldState::~CShieldState()
{
}

HRESULT CShieldState::Ready_State(CCharacter* pcharacter)
{
	pcharacter->Add_Weapon(WEAPONTYPE::SHIELD);

	return S_OK;
}

CWeaponState* CShieldState::Update_State(CCharacter* pcharacter, const float& fTimeDelta)
{

	CWeaponState* weapon = CWeaponState::Update_State(pcharacter, fTimeDelta);
	if (dynamic_cast<CShieldState*>(weapon))
	{
		return nullptr;
	}

	return weapon;
}

CShieldState* CShieldState::Create(CCharacter* pcharacter)
{
	CShieldState* pInstance = new CShieldState();

	if (FAILED(pInstance->Ready_State(pcharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShieldState::Free()
{

	CWeaponState::Free();
}
