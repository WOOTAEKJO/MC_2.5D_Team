#include "stdafx.h"
#include "..\Header\Drop1Look.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "ObjCreationMgr.h"

#include "Rich.h"
#include "RichPattern1Attack.h"

#include "Drop1Attack.h"
#include "RichPhase1IDLE.h"

CDrop1Look::CDrop1Look()
{
}

CDrop1Look::~CDrop1Look()
{
}

HRESULT CDrop1Look::Ready_State(CCharacter* pCharacter)
{
	static_cast<CMonster*>(pCharacter)->Set_ETCControl(true);
	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	
	if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE1) {
		static_cast<CRich*>(pCharacter)->ETC_Commenders_TargetSet(1);
	}
	else if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
		static_cast<CRich*>(pCharacter)->ETC_Commenders_TargetSet(2);
	}
	
	static_cast<CRich*>(pCharacter)->Create_ETC_Attack_Range();
	
	return S_OK;
}

CCharacterState* CDrop1Look::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	Add_Count(fTimeDelta);

	static_cast<CRich*>(pCharacter)->ETC_LookAT();
	static_cast<CRich*>(pCharacter)->HEAD_Target_Turn();
	if (m_fCount > 6.f)
	{
		return CDrop1Attack::Create(pCharacter);
	}

	return nullptr;
}

CDrop1Look* CDrop1Look::Create(CCharacter* pCharacter)
{
	CDrop1Look* pInstance = new CDrop1Look();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDrop1Look::Free(CCharacter* pCharacter)
{
}
