#include "stdafx.h"
#include "..\Header\HNPCBowReady.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "HNPCBowAttack.h"

CHNPCBowReady::CHNPCBowReady()
{
}

CHNPCBowReady::~CHNPCBowReady()
{
}

HRESULT CHNPCBowReady::Ready_State(CCharacter* pCharacter)
{
	pCharacter->Set_InitLook();	// �ִϸ��̼��� ���ư��� ���� �� ������ ����
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"READYBOW"));
	pCharacter->Add_SubWeapon(WEAPONTYPE::BOW);	// ȭ�� ����
	pCharacter->Set_IsRotate(true); // �ڵ����� ���ư��� ����

	return S_OK;
}

CCharacterState* CHNPCBowReady::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End())
	{
		return CHNPCBowAttack::Create(pCharacter);
	}
	return nullptr;
}

CHNPCBowReady* CHNPCBowReady::Create(CCharacter* pCharacter)
{
	CHNPCBowReady* pInstance = new CHNPCBowReady();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHNPCBowReady::Free(CCharacter* pCharacter)
{
}
