#include "stdafx.h"
#include "..\Header\HMIdle.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "HMWalk.h"
#include "ZombieAttack.h"
#include "SkeletonReady.h"

CHMIdle::CHMIdle()
{
}

CHMIdle::~CHMIdle()
{
}

HRESULT CHMIdle::Ready_State(CCharacter* pCharacter)
{
	if (static_cast<CHuman*>(pCharacter)->Get_MonsterType() == MOSTERID::GHOST) {
		static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"GHOSTIDLE"));
	}
	else {
		static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANIDLE"));
	}
	//pCharacter->Set_Push_Check(true);
	return S_OK;
}

CCharacterState* CHMIdle::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
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

	if (!pCharacter->Is_Arrived()) {
		return CHMWalk::Create(pCharacter);
	}

	return nullptr;
}

CHMIdle* CHMIdle::Create(CCharacter* pCharacter)
{
	CHMIdle* pInstance = new CHMIdle();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHMIdle::Free(CCharacter* pCharacter)
{
}
