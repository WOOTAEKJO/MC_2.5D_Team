#include "stdafx.h"
#include "..\Header\HighPriestRangeAttack.h"

#include "ObjCreationMgr.h"

#include "Export_Utility.h"
#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "LeaderDelay.h"

#include "Effect_Light3.h"
#include "Effect_Light3_Back.h"

CHighPriestRangeAttack::CHighPriestRangeAttack()
{
}

CHighPriestRangeAttack::~CHighPriestRangeAttack()
{
}

HRESULT CHighPriestRangeAttack::Ready_State(CCharacter* pCharacter)
{
	
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HIGHPRIESTRANGEATTACK"));
	pCharacter->Set_Push_Check(true);
	pCharacter->Set_SkillRunnig(true);
	pCharacter->Set_FullCount(false);

	CObjCreationMgr::GetInstance()->Create_Effect_Bottom<CEffect_Light3>(pCharacter->Get_Transform());
	//CObjCreationMgr::GetInstance()->Create_Effect_Back<CEffect_Light3_Back>(pCharacter->Get_Transform());


	return S_OK;
}

CCharacterState* CHighPriestRangeAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	Add_Count(fTimeDelta);
	m_fHealCount += fTimeDelta;

	if (m_fCount > 1.6f) {
		pCharacter->Set_Push_Check(false);
		pCharacter->Set_SkillRunnig(false);
		pCharacter->Set_FullCount(false);
		return CLeaderDelay::Create(pCharacter, 2.f);
	}

	if (m_fHealCount > 0.1f) {
		pCharacter->Priest_Range_Heal();
		m_fHealCount = 0.f;
	}

	return nullptr;
}

CHighPriestRangeAttack* CHighPriestRangeAttack::Create(CCharacter* pCharacter)
{
	CHighPriestRangeAttack* pInstance = new CHighPriestRangeAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHighPriestRangeAttack::Free(CCharacter* pCharacter)
{
}
