#include "stdafx.h"
#include "..\Header\ArchMageAttack.h"

#include "ObjCreationMgr.h"

#include "Export_Utility.h"
#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "LeaderDelay.h"
#include "LeaderIDLE.h"

//#include "ArchMazeBullet.h"
#include "ArchMazeBullet_CubeItem.h"


CArchMageAttack::CArchMageAttack()
{
}

CArchMageAttack::~CArchMageAttack()
{
}

HRESULT CArchMageAttack::Ready_State(CCharacter* pCharacter)
{
	//pCharacter->Set_InitLook();	// �ִϸ��̼��� ���ư��� ���� �� ������ ����
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"MAGEATTACK"));
	//pCharacter->Add_SubWeapon(WEAPONTYPE::BOW);	// ȭ�� ����
	//pCharacter->Set_IsRotate(true); // �ڵ����� ���ư��� ����

	return S_OK;
}

CCharacterState* CArchMageAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End()) {
		if (pCharacter->Get_Target() != nullptr) 
		{
			CObjCreationMgr::GetInstance()->Create_Bullet_CubeItem<CArchMazeBullet_CubeItem>(pCharacter);
			return CLeaderDelay::Create(pCharacter, 2.f);
		}
		else 
		{
			return CLeaderIDLE::Create(pCharacter);
		}
		
	}

	return nullptr;
}

CArchMageAttack* CArchMageAttack::Create(CCharacter* pCharacter)
{
	CArchMageAttack* pInstance = new CArchMageAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CArchMageAttack::Free(CCharacter* pCharacter)
{
}
