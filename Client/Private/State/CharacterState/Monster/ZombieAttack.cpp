#include "stdafx.h"
#include "..\Header\ZombieAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"

#include "HMWalk.h"
#include "HMIdle.h"
#include "HMonsterDelay.h"

#include "ObjCreationMgr.h"
#include "ScratchAttCol.h"

CZombieAttack::CZombieAttack()
{
}

CZombieAttack::~CZombieAttack()
{
}

HRESULT CZombieAttack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"ZOMBIEATTACK"));
	//pCharacter->Create_ATTColl(0.3f,_vec3(1.f,1.f,1.f),2.f);

	//pCharacter->Create_ATTColl(0.3f, _vec3(1.f, 1.f, 1.f), 2.f, OBJECTTYPE::MONSTER_BULLET, pCharacter);

	CObjCreationMgr::GetInstance()->Create_ATTColl<CScratchAttCol>(0.2f, _vec3(1.f, 1.f, 1.f), 2.f, pCharacter->Get_Damage(), OBJECTTYPE::MONSTER_BULLET, pCharacter);

	//pCharacter->Set_Push_Check(true);

	return S_OK;
}

CCharacterState* CZombieAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	
	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End())
	{
		pCharacter->Set_Push_Check(false);
		return CHMonsterDelay::Create(pCharacter,1.f);
	}

	return nullptr;
}

CZombieAttack* CZombieAttack::Create(CCharacter* pCharacter)
{
	CZombieAttack* pInstance = new CZombieAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CZombieAttack::Free(CCharacter* pCharacter)
{
}
