#include "stdafx.h"
#include "..\Header\RichGroggy.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "Rich.h"
#include "RichPattern1Attack.h"

#include "RichPhase1IDLE.h"

CRichGroggy::CRichGroggy()
{
}

CRichGroggy::~CRichGroggy()
{
}

HRESULT CRichGroggy::Ready_State(CCharacter* pCharacter)
{
	static_cast<CMonster*>(pCharacter)->Set_ETCControl(false);
	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHGROGGY"));
	static_cast<CMonster*>(pCharacter)->Set_DamagableCheck(true);
	m_iCurHP = static_cast<CMonster*>(pCharacter)->Get_HP();
	return S_OK;
}

CCharacterState* CRichGroggy::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	Add_Count(fTimeDelta);

	//if (m_fCount > 3.f)
	//{
	//	static_cast<CRich*>(pCharacter)->Set_GroggyCheck(false);
	//	static_cast<CRich*>(pCharacter)->Set_SummonCheck(true);
	//	/*switch (static_cast<CRich*>(pCharacter)->Get_PhaseType())
	//	{
	//	case CRich::RICHPHASETYPE::GROGGY:
	//		break;
	//	case CRich::RICHPHASETYPE::PHASE1:
	//		
	//	case CRich::RICHPHASETYPE::PHASE2:
	//		break;
	//	default:
	//		break;
	//	}*/
	//	return CRichPhase1IDLE::Create(pCharacter);
	//}

	if (static_cast<CRich*>(pCharacter)->Get_PhaseChangeCheck()) {
		static_cast<CRich*>(pCharacter)->Set_GroggyCheck(false);
		static_cast<CRich*>(pCharacter)->Set_SummonCheck(true);
		static_cast<CMonster*>(pCharacter)->Set_DamagableCheck(false);
		return CRichPhase1IDLE::Create(pCharacter);
	}

	if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
	
		_float iHP = static_cast<CRich*>(pCharacter)->Get_HP();
		_float iMaxHP = static_cast<CRich*>(pCharacter)->Get_MaxHP();
		_float iCal = iMaxHP * (25.f / 100.f);
		if ((m_iCurHP - iHP) > iCal) {
			static_cast<CRich*>(pCharacter)->Set_GroggyCheck(false);
			static_cast<CRich*>(pCharacter)->Set_SummonCheck(true);
			static_cast<CMonster*>(pCharacter)->Set_DamagableCheck(false);
			return CRichPhase1IDLE::Create(pCharacter);
		}
	}

	

	return nullptr;
}

CRichGroggy* CRichGroggy::Create(CCharacter* pCharacter)
{
	CRichGroggy* pInstance = new CRichGroggy();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichGroggy::Free(CCharacter* pCharacter)
{
}
