#include "stdafx.h"
#include "..\Header\RichPattern1Delay.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "RichIDLE.h"
#include "RichPhase1IDLE.h"

#include "Rich.h"

CRichPattern1Delay::CRichPattern1Delay()
{
}

CRichPattern1Delay::~CRichPattern1Delay()
{
}

HRESULT CRichPattern1Delay::Ready_State(CCharacter* pCharacter)
{
	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	return S_OK;
}

CCharacterState* CRichPattern1Delay::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);
	
	if (m_fCount > 1.f) {
		static_cast<CMonster*>(pCharacter)->Set_ETCControl(false);
		static_cast<CRich*>(pCharacter)->Set_SummonCheck(true);
		static_cast<CRich*>(pCharacter)->Set_FlasherCheck(false);
		static_cast<CRich*>(pCharacter)->Delete_ETC_Attack_Range();
		/*switch (static_cast<CRich*>(pCharacter)->Get_PhaseType())
		{
		case CRich::RICHPHASETYPE::GROGGY:
			break;
		case CRich::RICHPHASETYPE::PHASE1:
			return CRichPhase1IDLE::Create(pCharacter);
		case CRich::RICHPHASETYPE::PHASE2:
			break;
		default:
			break;
		}*/
		return CRichPhase1IDLE::Create(pCharacter);
	}
	
	return nullptr;
}

CRichPattern1Delay* CRichPattern1Delay::Create(CCharacter* pCharacter)
{
	CRichPattern1Delay* pInstance = new CRichPattern1Delay();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichPattern1Delay::Free(CCharacter* pCharacter)
{
}
