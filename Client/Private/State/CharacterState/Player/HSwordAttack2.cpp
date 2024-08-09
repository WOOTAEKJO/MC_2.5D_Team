#include "stdafx.h"
#include "..\Header\HSwordAttack2.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "HIdle.h"
#include "HWalk.h"

#include "GameObject.h"
#include "TestBullet.h"

CHSwordAttack2::CHSwordAttack2()
{
}

CHSwordAttack2::~CHSwordAttack2()
{
}

HRESULT CHSwordAttack2::Ready_State(CCharacter* pCharacter)
{

	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANSWORDATTACK3"));
	pCharacter->Set_IsRotate(true);	

	return S_OK;
}

CCharacterState* CHSwordAttack2::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	//pCharacter->Create_Bullet();
	pCharacter->Create_ATTColl(0.3f, _vec3(1.f, 1.f, 1.f), 2.f, OBJECTTYPE::ALLY_BULLET, pCharacter);

	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End())
	{
		//pCharacter->Set_IsRotate(false);
		return CHIdle::Create(pCharacter);
	}
		


	return nullptr;
}

CHSwordAttack2* CHSwordAttack2::Create(CCharacter* pCharacter)
{
	CHSwordAttack2* pInstance = new CHSwordAttack2();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHSwordAttack2::Free(CCharacter* pCharacter)
{
}
