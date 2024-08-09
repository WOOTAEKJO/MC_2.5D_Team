#include "stdafx.h"
#include "..\Header\HNPCBowAttack.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HNPCDelay.h"

#include "Arrow.h"

CHNPCBowAttack::CHNPCBowAttack()
{
}

CHNPCBowAttack::~CHNPCBowAttack()
{
}

HRESULT CHNPCBowAttack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"BOWATTACK"));

	return S_OK;
}

CCharacterState* CHNPCBowAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End())
	{
		static_cast<CArrow*>(pCharacter->Get_SubWeapon())->Set_ShotCheck();
		
		return CHNPCDelay::Create(pCharacter, 3.f);
	}
	return nullptr;
}

CHNPCBowAttack* CHNPCBowAttack::Create(CCharacter* pCharacter)
{
	CHNPCBowAttack* pInstance = new CHNPCBowAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHNPCBowAttack::Free(CCharacter* pCharacter)
{
}
