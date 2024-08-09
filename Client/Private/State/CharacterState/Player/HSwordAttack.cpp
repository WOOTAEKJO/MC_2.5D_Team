#include "stdafx.h"
#include "..\Header\HSwordAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "HIdle.h"
#include "HWalk.h"
#include "HSwordAttack2.h"

#include "GameObject.h"
#include "TestBullet.h"

CHSwordAttack::CHSwordAttack()
{
}

CHSwordAttack::~CHSwordAttack()
{
}

HRESULT CHSwordAttack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANSWORDATTACK2"));

	//pCharacter->Create_Bullet();
	pCharacter->Create_ATTColl(0.3f, _vec3(1.f, 1.f, 1.f), 2.f, OBJECTTYPE::ALLY_BULLET, pCharacter);

	return S_OK;
}

CCharacterState* CHSwordAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End())
		return CHIdle::Create(pCharacter);



	if (Get_Count() > 0.3f) {
		if (Engine::CInputDev::GetInstance()->Key_Pressing(DIK_F)) {
			return CHSwordAttack2::Create(pCharacter);
		}
		//if (!pCharacter->Is_Arrived()) {
		//	return CHWalk::Create(pCharacter);
		//}
		
	}





	return nullptr;
}

CHSwordAttack* CHSwordAttack::Create(CCharacter* pCharacter)
{
	CHSwordAttack* pInstance = new CHSwordAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHSwordAttack::Free(CCharacter* pCharacter)
{
}
