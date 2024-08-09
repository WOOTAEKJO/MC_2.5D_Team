#include "stdafx.h"
#include "..\Header\RichPhase1IDLE.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "RichPattern1Look.h"
#include "RichGroggy.h"

#include "Drop1Look.h"

#include "RichLaserReady.h"

#include "Rich.h"

#include "RichChange.h"

CRichPhase1IDLE::CRichPhase1IDLE()
{
}

CRichPhase1IDLE::~CRichPhase1IDLE()
{
}

HRESULT CRichPhase1IDLE::Ready_State(CCharacter* pCharacter)
{

	if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE1) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	}
	else if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHPHASE1IDLE"));
	}
	

	return S_OK;
}

CCharacterState* CRichPhase1IDLE::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (static_cast<CRich*>(pCharacter)->Get_PhaseChangeCheck()) {
		return CRichChange::Create(pCharacter);
	}

	if (static_cast<CRich*>(pCharacter)->Get_FlasherCheck()) {
		
		if (m_fCount > 0.5f) {
			//static_cast<CRich*>(pCharacter)->Set_FlasherCheck(true);
			return CRichPattern1Look::Create(pCharacter);
			m_fCount = 0.f;
		}
	}
	else if (static_cast<CRich*>(pCharacter)->Get_GroggyCheck()) {
		if (m_fCount > 0.5f) {
			//static_cast<CRich*>(pCharacter)->Set_FlasherCheck(true);
			return CRichGroggy::Create(pCharacter);
			m_fCount = 0.f;
		}
	}
	else if (static_cast<CRich*>(pCharacter)->Get_LaserCheck()) {
		return CRichLaserReady::Create(pCharacter);
		//m_fCount = 0.f;
	}
	else {
		
		if (m_fCount > 3.f) {
			return CDrop1Look::Create(pCharacter);
			m_fCount = 0.f;
		}
	}
	
	/*if (Engine::Key_Down(DIK_E)) {
		return CRichLaserReady::Create(pCharacter);
	}*/


	return nullptr;
}

CRichPhase1IDLE* CRichPhase1IDLE::Create(CCharacter* pCharacter)
{
	CRichPhase1IDLE* pInstance = new CRichPhase1IDLE();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichPhase1IDLE::Free(CCharacter* pCharacter)
{
}
