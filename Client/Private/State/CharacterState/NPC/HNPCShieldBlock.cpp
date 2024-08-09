#include "stdafx.h"
#include "..\Header\HNPCShieldBlock.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "ObjCreationMgr.h"

#include "HNPCDelay.h"


CHNPCShieldBlock::CHNPCShieldBlock()
{
}

CHNPCShieldBlock::~CHNPCShieldBlock()
{
}

HRESULT CHNPCShieldBlock::Ready_State(CCharacter* pCharacter)
{
	pCharacter->Set_Push_Check(true);
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"SHIELDBLOCK"));
	

	return S_OK;
}

CCharacterState* CHNPCShieldBlock::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (pCharacter->Is_Target_Dead())
	{
		pCharacter->Set_Push_Check(false);
		return CHNPCDelay::Create(pCharacter, 1.f);
	}

	if (m_fCount > 5.f) {
		pCharacter->Recovery(10.f);
		m_fCount = 0.f;
	}

	return nullptr;
}

CHNPCShieldBlock* CHNPCShieldBlock::Create(CCharacter* pCharacter)
{
	CHNPCShieldBlock* pInstance = new CHNPCShieldBlock();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHNPCShieldBlock::Free(CCharacter* pCharacter)
{
}
