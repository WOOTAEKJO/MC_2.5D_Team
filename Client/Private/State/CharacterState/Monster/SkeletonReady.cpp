#include "stdafx.h"
#include "..\Header\SkeletonReady.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "SkeletonAttack.h"

CSkeletonReady::CSkeletonReady()
{
}

CSkeletonReady::~CSkeletonReady()
{
}

HRESULT CSkeletonReady::Ready_State(CCharacter* pCharacter)
{
	pCharacter->Set_InitLook();	// �ִϸ��̼��� ���ư��� ���� �� ������ ����
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"READYBOW"));
	pCharacter->Add_SubWeapon(WEAPONTYPE::BOW);	// ȭ�� ����
	pCharacter->Set_IsRotate(true); // �ڵ����� ���ư��� ����

	return S_OK;
}

CCharacterState* CSkeletonReady::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End())
	{
		return CSkeletonAttack::Create(pCharacter);
	}
	return nullptr;
}

CSkeletonReady* CSkeletonReady::Create(CCharacter* pCharacter)
{
	CSkeletonReady* pInstance = new CSkeletonReady();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkeletonReady::Free(CCharacter* pCharacter)
{
}
