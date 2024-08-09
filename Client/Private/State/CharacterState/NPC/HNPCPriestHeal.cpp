#include "stdafx.h"
#include "..\Header\HNPCPriestHeal.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "ObjCreationMgr.h"

#include "HNPCDelay.h"
#include "HNPCIDLE.h"

#include "Effect_Heal6.h"


CHNPCPriestHeal::CHNPCPriestHeal()
{
}

CHNPCPriestHeal::~CHNPCPriestHeal()
{
}

HRESULT CHNPCPriestHeal::Ready_State(CCharacter* pCharacter)
{

	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"PRIESTHEAL"));
	return S_OK;
}

CCharacterState* CHNPCPriestHeal::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (pCharacter->Is_Target_Dead())
	{

		return CHNPCIDLE::Create(pCharacter);
	}

	if (!pCharacter->Is_Target_Around(*pCharacter->Get_Target()->Get_Transform()
		->Get_Pos(),25.f)) {
		return CHNPCDelay::Create(pCharacter, 1.f);
	}

	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End()) {
		pCharacter->Recovery_Target(10.f);
		_vec3 targetPos = *pCharacter->Get_Target()->Get_Transform()->Get_Pos();
		targetPos.y -= 0.5f;
		CObjCreationMgr::GetInstance()->Create_Effect<CEffect_Heal6>(targetPos);
		return CHNPCDelay::Create(pCharacter, 3.f);
	}
	return nullptr;
}

CHNPCPriestHeal* CHNPCPriestHeal::Create(CCharacter* pCharacter)
{
	CHNPCPriestHeal* pInstance = new CHNPCPriestHeal();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHNPCPriestHeal::Free(CCharacter* pCharacter)
{
}
