#include "stdafx.h"
#include "..\Header\HIdle.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HWalk.h"
#include "HAttack.h"
#include "HHooray.h"

CHIdle::CHIdle()
{
}

CHIdle::~CHIdle()
{
}

HRESULT CHIdle::Ready_State(CCharacter* pCharacter)
{
	pCharacter->Set_IsRotate(false);
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANIDLE"));
	return S_OK;
}

CCharacterState* CHIdle::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (!pCharacter->Is_Arrived()) {
		return CHWalk::Create(pCharacter);
	}

	if (Engine::CInputDev::GetInstance()->Key_Down(DIK_F)) {
		return CHAttack::Create(pCharacter);
	}

	/*if (Engine::CInputDev::GetInstance()->Key_Down(DIK_H)) {
		CHuman* human = dynamic_cast<CHuman*>(pCharacter);
		if (human) 
		{
			return CHHooray::Create(human);
		}
	}*/

	return nullptr;
}

CHIdle* CHIdle::Create(CCharacter* pCharacter)
{
	CHIdle* pInstance = new CHIdle();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHIdle::Free(CCharacter* pCharacter)
{
}
