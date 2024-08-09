#include "stdafx.h"
#include "..\Header\HBowAttack.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "HIdle.h"
#include "HWalk.h"


#include "GameObject.h"
#include "Arrow.h"


CHBowAttack::CHBowAttack()
{
}

CHBowAttack::~CHBowAttack()
{
}

HRESULT CHBowAttack::Ready_State(CCharacter* pCharacter)
{

	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"BOWATTACK"));
	
	return S_OK;
}

CCharacterState* CHBowAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End()) {
		static_cast<CArrow*>(pCharacter->Get_SubWeapon())->Set_ShotCheck();
		//pCharacter->Set_IsRotate(false);
		return CHIdle::Create(pCharacter);
	}

	return nullptr;
}

CHBowAttack* CHBowAttack::Create(CCharacter* pCharacter)
{
	CHBowAttack* pInstance = new CHBowAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHBowAttack::Free(CCharacter* pCharacter)
{
	
}
