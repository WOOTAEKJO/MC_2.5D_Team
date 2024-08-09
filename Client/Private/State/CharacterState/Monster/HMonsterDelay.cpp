#include "stdafx.h"
#include "..\Header\HMonsterDelay.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HMWalk.h"
#include "HMIdle.h"

CHMonsterDelay::CHMonsterDelay()
{
}

CHMonsterDelay::~CHMonsterDelay()
{
}

HRESULT CHMonsterDelay::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>( pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANIDLE"));
	//pCharacter->Set_Push_Check(true);
	return S_OK;
}

CCharacterState* CHMonsterDelay::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	switch (pCharacter->Get_WeaponType())
	{
	case WEAPONTYPE::SWORD:
		break;
	case WEAPONTYPE::BOW:
		pCharacter->Set_IsRotate(false); // 자동으로 돌아가기 해제
		break;
	default:
		break;
	}

	pCharacter->Target_Dir_Update();
	static_cast<CHuman*>(pCharacter)->Update_Dir_To_Destination();

	if (Get_Count() > m_fDelTime) {
		return CHMIdle::Create(pCharacter);
	}

	return nullptr;
}

CHMonsterDelay* CHMonsterDelay::Create(CCharacter* pCharacter,const _float& fDelTime)
{
	CHMonsterDelay* pInstance = new CHMonsterDelay();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}
	pInstance->Set_DelTime(fDelTime);

	return pInstance;
}

void CHMonsterDelay::Free(CCharacter* pCharacter)
{
}
