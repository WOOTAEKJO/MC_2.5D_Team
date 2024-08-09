#include "stdafx.h"
#include "..\Header\HNPCSwordAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "ObjCreationMgr.h"
#include "SwordATTCol.h"

CHNPCSwordAttack::CHNPCSwordAttack()
{
}

CHNPCSwordAttack::~CHNPCSwordAttack()
{
}

HRESULT CHNPCSwordAttack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANSWORDATTACK1"));

	//pCharacter->Create_ATTColl(0.3f, _vec3(1.f, 1.f, 1.f), 2.f, OBJECTTYPE::ALLY_BULLET, pCharacter);

	CObjCreationMgr::GetInstance()->Create_ATTColl<CSwordATTCol>(0.3f, _vec3(1.2f, 1.2f, 1.2f), 3.f, pCharacter->Get_Damage(), OBJECTTYPE::ALLY_BULLET, pCharacter);

	return S_OK;
}

CCharacterState* CHNPCSwordAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	CCharacterState* state = CHNPCAttack::Update_State(pCharacter, fTimeDelta);
	if (state != nullptr)
	{
		return state;
	}

	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End())
	{
		return CHNPCDelay::Create(pCharacter, 1.f);
	}
	return nullptr;
}

CHNPCSwordAttack* CHNPCSwordAttack::Create(CCharacter* pCharacter)
{
	CHNPCSwordAttack* pInstance = new CHNPCSwordAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHNPCSwordAttack::Free(CCharacter* pCharacter)
{
}
