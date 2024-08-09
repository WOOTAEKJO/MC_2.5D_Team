#include "stdafx.h"
#include "..\Header\HWalk.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "HIdle.h"
#include "HAttack.h"

CHWalk::CHWalk()
{
}

CHWalk::~CHWalk()
{
}

HRESULT CHWalk::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANWALK"));
	//pCharacter->Set_IsRotate(true);
	return S_OK;
}

CCharacterState* CHWalk::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (pCharacter->Is_Arrived()) {
		//pCharacter->Set_IsRotate(false);
		return CHIdle::Create(pCharacter);
	}

	if (Engine::CInputDev::GetInstance()->Key_Down(DIK_F)) {
		return CHAttack::Create(pCharacter);
	}

	return nullptr;
}

CHWalk* CHWalk::Create(CCharacter* pCharacter)
{
	CHWalk* pInstance = new CHWalk();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHWalk::Free(CCharacter* pCharacter)
{
}
