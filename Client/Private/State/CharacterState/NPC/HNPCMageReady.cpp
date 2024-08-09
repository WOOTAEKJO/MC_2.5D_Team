#include "stdafx.h"
#include "..\Header\HNPCMageReady.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "HNPCMageAttack.h"


CHNPCMageReady::CHNPCMageReady()
{
}

CHNPCMageReady::~CHNPCMageReady()
{
}

HRESULT CHNPCMageReady::Ready_State(CCharacter* pCharacter)
{
	//pCharacter->Set_InitLook();	// 애니메이션이 돌아가기 전에 룩 방향을 저장
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"MAGEREADY"));
	//pCharacter->Add_SubWeapon(WEAPONTYPE::BOW);	// 화살 생성
	//pCharacter->Set_IsRotate(true); // 자동으로 돌아가기 해제

	return S_OK;
}

CCharacterState* CHNPCMageReady::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_fCount>5.f)
	{
		return CHNPCMageAttack::Create(pCharacter);
	}
	return nullptr;
}

CHNPCMageReady* CHNPCMageReady::Create(CCharacter* pCharacter)
{
	CHNPCMageReady* pInstance = new CHNPCMageReady();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHNPCMageReady::Free(CCharacter* pCharacter)
{
}
