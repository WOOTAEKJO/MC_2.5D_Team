#include "stdafx.h"
#include "..\Header\HAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"


#include "SaveLoadMgr.h"
#include "HIdle.h"
#include "HWalk.h"
#include "HSwordAttack.h"
#include "HBowAttack.h"

#include "GameObject.h"
#include "TestBullet.h"

#include "ObjCreationMgr.h"

#include "TestBullet.h"
#include "TestBullet2.h"
#include "TestBullet3.h"
#include "TestBullet4.h"

#include "ObjCreationMgr.h"


CHAttack::CHAttack()
{
}

CHAttack::~CHAttack()
{
}

HRESULT CHAttack::Ready_State(CCharacter* pCharacter)
{
	switch (pCharacter->Get_WeaponType())
	{
	case WEAPONTYPE::SWORD:
		static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANSWORDATTACK1"));
		pCharacter->Create_ATTColl(0.3f, _vec3(1.2f, 1.f, 1.2f), 3.f,OBJECTTYPE::ALLY_BULLET, pCharacter);
		break;
	case WEAPONTYPE::BOW:
		pCharacter->Set_InitLook();	// �ִϸ��̼��� ���ư��� ���� �� ������ ����
		static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"READYBOW"));
		pCharacter->Add_SubWeapon(WEAPONTYPE::BOW);	// ȭ�� ����
		pCharacter->Set_IsRotate(true); // �ڵ����� ���ư��� ����
		break;
	default:
		static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANNONATTACK"));
		pCharacter->Init_FrameCount(5);
		static_cast<CHuman*>(pCharacter)->Set_FrameSpeed(30.f);
		pCharacter->Create_ATTColl(0.3f, _vec3(1.f, 1.f, 1.f), 2.f, OBJECTTYPE::ALLY_BULLET, pCharacter);
		
		CObjCreationMgr::GetInstance()->Create_Bullet_Meteor<CTestBullet3>(pCharacter);
		break;
	}

	

	//pCharacter->Create_Bullet();

	return S_OK;
}

CCharacterState* CHAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (pCharacter->Get_WeaponType() == WEAPONTYPE::BOW) {
		if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End()) {
			return CHBowAttack::Create(pCharacter);
		}
		
	}else if (Get_Count() > 0.6f) {
		pCharacter->Set_IsRotate(false);
		return CHIdle::Create(pCharacter);
	}

	
	/*if (pCharacter->Is_Animation_Frame_End())
		return CHIdle::Create(pCharacter);*/



	if (Get_Count() > 0.5f) {
		if (Engine::CInputDev::GetInstance()->Key_Pressing(DIK_F)) {
			switch (pCharacter->Get_WeaponType())
			{
			case WEAPONTYPE::SWORD:
				pCharacter->Set_IsRotate(false);
				return CHSwordAttack::Create(pCharacter);
				
			default:
				pCharacter->Set_IsRotate(false);
				return CHAttack::Create(pCharacter);
			}
			
		}
		if (!pCharacter->Is_Arrived()) {
			pCharacter->Set_IsRotate(false);
			return CHWalk::Create(pCharacter);
		}
		
	}

	

	return nullptr;
}

CHAttack* CHAttack::Create(CCharacter* pCharacter)
{
	CHAttack* pInstance = new CHAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHAttack::Free(CCharacter* pCharacter)
{
}
