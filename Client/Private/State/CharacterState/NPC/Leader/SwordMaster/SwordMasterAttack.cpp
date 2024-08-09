#include "stdafx.h"
#include "..\Header\SwordMasterAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "LeaderDelay.h"

#include "SwordMasterATTCol.h"

CSwordMasterAttack::CSwordMasterAttack()
{
}

CSwordMasterAttack::~CSwordMasterAttack()
{
}

HRESULT CSwordMasterAttack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANSWORDATTACK1"));
	CObjCreationMgr::GetInstance()->Create_ATTColl<CSwordMasterATTCol>(0.2f, _vec3(2.f, 2.f, 2.f), 2.f, 10.f, OBJECTTYPE::ALLY_BULLET, pCharacter);
	//pCharacter->Create_ATTColl(0.3f, _vec3(1.5f, 1.5f, 1.5f), 2.f, OBJECTTYPE::ALLY_BULLET, pCharacter);
	return S_OK;
}

CCharacterState* CSwordMasterAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End()) {
		
		return CLeaderDelay::Create(pCharacter, 1.f);
	}
	return nullptr;
}

CSwordMasterAttack* CSwordMasterAttack::Create(CCharacter* pCharacter)
{
	CSwordMasterAttack* pInstance = new CSwordMasterAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSwordMasterAttack::Free(CCharacter* pCharacter)
{
}
