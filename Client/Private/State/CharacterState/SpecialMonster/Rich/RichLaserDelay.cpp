#include "stdafx.h"
#include "..\Header\RichLaserDelay.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "RichPattern1Look.h"
#include "RichGroggy.h"

#include "Rich.h"

#include "RichPhase1IDLE.h"

CRichLaserDelay::CRichLaserDelay()
{
}

CRichLaserDelay::~CRichLaserDelay()
{
}

HRESULT CRichLaserDelay::Ready_State(CCharacter* pCharacter)
{

	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));


	return S_OK;
}

CCharacterState* CRichLaserDelay::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_fCount > 3.f) {
		
		//static_cast<CMonster*>(pCharacter)->Set_ETCControl(false);
		//static_cast<CRich*>(pCharacter)->Delete_ETC_Attack_Range();
		//static_cast<CRich*>(pCharacter)->Set_FlasherCheck(false);
		static_cast<CRich*>(pCharacter)->Set_LaserCheck(false);
		static_cast<CRich*>(pCharacter)->Set_SummonCheck(true);
		/*switch (static_cast<CRich*>(pCharacter)->Get_PhaseType())
		{
		case CRich::RICHPHASETYPE::GROGGY:
			break;
		case CRich::RICHPHASETYPE::PHASE1:
			
		case CRich::RICHPHASETYPE::PHASE2:
			break;
		default:
			break;
		}*/
		return CRichPhase1IDLE::Create(pCharacter);
		
	}

	return nullptr;
}

CRichLaserDelay* CRichLaserDelay::Create(CCharacter* pCharacter)
{
	CRichLaserDelay* pInstance = new CRichLaserDelay();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichLaserDelay::Free(CCharacter* pCharacter)
{
}
