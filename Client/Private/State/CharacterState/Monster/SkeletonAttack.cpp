#include "stdafx.h"
#include "..\Header\SkeletonAttack.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HMonsterDelay.h"

#include "Arrow.h"

CSkeletonAttack::CSkeletonAttack()
{
}

CSkeletonAttack::~CSkeletonAttack()
{
}

HRESULT CSkeletonAttack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"BOWATTACK"));

	return S_OK;
}

CCharacterState* CSkeletonAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End())
	{
		static_cast<CArrow*>(pCharacter->Get_SubWeapon())->Set_ShotCheck();

		return CHMonsterDelay::Create(pCharacter, 3.f);
	}
	return nullptr;
}

CSkeletonAttack* CSkeletonAttack::Create(CCharacter* pCharacter)
{
	CSkeletonAttack* pInstance = new CSkeletonAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkeletonAttack::Free(CCharacter* pCharacter)
{
}
