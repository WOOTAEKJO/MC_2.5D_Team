#include "stdafx.h"
#include "..\Header\HNPCMageAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "ObjCreationMgr.h"

#include "HNPCDelay.h"

//#include "TestBullet4.h"
//#include "TestBullet2.h"
//#include "FireBall.h"
//#include "FireBall2.h"
#include "FireBall_CubeItem.h"

CHNPCMageAttack::CHNPCMageAttack()
{
}

CHNPCMageAttack::~CHNPCMageAttack()
{
}

HRESULT CHNPCMageAttack::Ready_State(CCharacter* pCharacter)
{
	//pCharacter->Set_InitLook();	// �ִϸ��̼��� ���ư��� ���� �� ������ ����
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"MAGEATTACK"));
	//pCharacter->Add_SubWeapon(WEAPONTYPE::BOW);	// ȭ�� ����
	//pCharacter->Set_IsRotate(true); // �ڵ����� ���ư��� ����
	
	return S_OK;
}

CCharacterState* CHNPCMageAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	CGameObject* pTarget = pCharacter->Get_Target();

	if (pTarget == nullptr || pCharacter->Is_Target_Dead()) {
		return CHNPCDelay::Create(pCharacter, 0.f);
	}
	if (pTarget->Get_Transform()->Get_Pos() == nullptr) {
		return CHNPCDelay::Create(pCharacter, 0.f);
	}

	if (pTarget->Get_Transform()->Get_WorldMatrix()->m[3] == nullptr) {
		return CHNPCDelay::Create(pCharacter, 0.f);
	}

	if (!pCharacter->Is_Target_Around(*pTarget->Get_Transform()->Get_Pos(), 30.f)) {
		return CHNPCDelay::Create(pCharacter, 0.f);
	}


	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End())
	{
		/*CObjCreationMgr::GetInstance()->Create_Bullet_Fire<CFireBullet>(pCharacter, pCharacter->Get_Target()
			->Get_Transform()->Get_Pos());*/
		CObjCreationMgr::GetInstance()->Create_Bullet_CubeItem<CFireBall_CubeItem>(pCharacter);

		return CHNPCDelay::Create(pCharacter,1.f);
	}
	return nullptr;
}

CHNPCMageAttack* CHNPCMageAttack::Create(CCharacter* pCharacter)
{
	CHNPCMageAttack* pInstance = new CHNPCMageAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHNPCMageAttack::Free(CCharacter* pCharacter)
{
}
