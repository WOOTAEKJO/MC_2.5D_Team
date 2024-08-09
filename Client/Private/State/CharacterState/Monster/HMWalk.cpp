#include "stdafx.h"
#include "..\Header\HMWalk.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "ZombieAttack.h"
#include "SkeletonReady.h"
#include "HMIdle.h"

CHMWalk::CHMWalk()
{
}

CHMWalk::~CHMWalk()
{
}

HRESULT CHMWalk::Ready_State(CCharacter* pCharacter)
{
	if (static_cast<CHuman*>(pCharacter)->Get_MonsterType() == MOSTERID::GHOST) {
		static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"GHOSTIDLE"));
	}
	else {
		static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANWALK"));
	}
	pCharacter->Set_Push_Check(false);
	return S_OK;
}

CCharacterState* CHMWalk::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	
	switch (pCharacter->Get_WeaponType())
	{
	case WEAPONTYPE::SWORD:
		if (static_cast<CHuman*>(pCharacter)->Attack_Stance(3.7f)) {
			return CZombieAttack::Create(pCharacter);
		}

		break;
	case WEAPONTYPE::BOW:

		if (static_cast<CHuman*>(pCharacter)->Attack_Stance(20.f)) {
			return CSkeletonReady::Create(pCharacter);
		}

		break;
	default:
		if (static_cast<CHuman*>(pCharacter)->Attack_Stance(3.7f)) {
			return CZombieAttack::Create(pCharacter);
		}
		break;
	}


	if (pCharacter->Is_Arrived()) {
		return CHMIdle::Create(pCharacter);
	}

	pCharacter->Move(fTimeDelta);

	return nullptr;
}

CHMWalk* CHMWalk::Create(CCharacter* pCharacter)
{
	CHMWalk* pInstance = new CHMWalk();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHMWalk::Free(CCharacter* pCharacter)
{
}
