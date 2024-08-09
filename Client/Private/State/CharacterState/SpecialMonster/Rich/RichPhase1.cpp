#include "stdafx.h"
#include "..\Header\RichPhase1.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "RichPattern1Look.h"
#include "RichPhase1IDLE.h"

#include "Drop1Look.h"
#include "RichDead.h"

#include "Rich.h"

CRichPhase1::CRichPhase1()
{
}

CRichPhase1::~CRichPhase1()
{
}

HRESULT CRichPhase1::Ready_State(CCharacter* pCharacter)
{

	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	static_cast<CRich*>(pCharacter)->Set_SummonCheck(true);
	static_cast<CRich*>(pCharacter)->Set_PhaseType(CRich::RICHPHASETYPE::PHASE1);
	m_pState = CRichPhase1IDLE::Create(pCharacter);

	m_eSumType = SUMMONTYPE::ZOMBIE_SUM;

	return S_OK;
}

CCharacterState* CRichPhase1::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	//pCharacter->Ready_Dead();
	if (pCharacter->Get_HP() <= 0) {
		static_cast<CRich*>(pCharacter)->Delete_Summoner();
		return CRichDead::Create(pCharacter);
	}
	else {

		CCharacterState* HumanState = m_pState->Update_State(pCharacter, fTimeDelta);
		if (HumanState != nullptr)
		{
			HumanState->Free(pCharacter);
			Safe_Delete(m_pState);
			m_pState = HumanState;
		}

		if (static_cast<CRich*>(pCharacter)->Get_LaserCheck()) {
			static_cast<CRich*>(pCharacter)->Delete_Summoner();
			m_eSumType = SUMMONTYPE::ZOMBIE_SUM;
			m_fCount = 0.f;
		}

		if (!static_cast<CRich*>(pCharacter)->Get_FlasherCheck() &&
			!static_cast<CRich*>(pCharacter)->Get_GroggyCheck() &&
			!static_cast<CRich*>(pCharacter)->Get_LaserCheck()) {
			Crystal_State(pCharacter, fTimeDelta);
			static_cast<CRich*>(pCharacter)->Summoner(m_eSumType);
		}
	}

	

	return nullptr;
}

void CRichPhase1::Crystal_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_eSumType == SUMMONTYPE::ZOMBIE_SUM) {
		
		if (m_fCount > 7.f) {
			m_eSumType = SUMMONTYPE::CRYSTAL_SUM;
			static_cast<CRich*>(pCharacter)->Set_SummonCheck(true);
			m_fCount = 0.f;
		}
	}else if (m_eSumType == SUMMONTYPE::CRYSTAL_SUM) {

		if (static_cast<CRich*>(pCharacter)->Is_Summon_Dead()) {
			static_cast<CRich*>(pCharacter)->Delete_Summoner();
			m_eSumType = SUMMONTYPE::ZOMBIE_SUM;
			static_cast<CRich*>(pCharacter)->Set_GroggyCheck(true);
			m_fCount = 0.f;
		}
		else if (m_fCount > 18.f) {
			static_cast<CRich*>(pCharacter)->Delete_Summoner();
			m_eSumType = SUMMONTYPE::ZOMBIE_SUM;
			static_cast<CRich*>(pCharacter)->Set_FlasherCheck(true);
			m_fCount = 0.f;
			
		}
	}
}

CRichPhase1* CRichPhase1::Create(CCharacter* pCharacter)
{
	CRichPhase1* pInstance = new CRichPhase1();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichPhase1::Free(CCharacter* pCharacter)
{
}
