#include "stdafx.h"
#include "..\Header\RichPattern1Look.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "Rich.h"
#include "RichPattern1Attack.h"

CRichPattern1Look::CRichPattern1Look()
{
}

CRichPattern1Look::~CRichPattern1Look()
{
}

HRESULT CRichPattern1Look::Ready_State(CCharacter* pCharacter)
{
	static_cast<CMonster*>(pCharacter)->Set_ETCControl(true);
	
	if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE1) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	}
	else if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHDROP"));
	}

	static_cast<CRich*>(pCharacter)->Reset_Random_Pos();
	static_cast<CRich*>(pCharacter)->Create_ETC_Attack_Range();

	return S_OK;
}

CCharacterState* CRichPattern1Look::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	Add_Count(fTimeDelta);

	static_cast<CRich*>(pCharacter)->ETC_LookAT();

	if (m_fCount > 6.f)
	{
		return CRichPattern1Attack::Create(pCharacter);
	}

	return nullptr;
}

CRichPattern1Look* CRichPattern1Look::Create(CCharacter* pCharacter)
{
	CRichPattern1Look* pInstance = new CRichPattern1Look();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichPattern1Look::Free(CCharacter* pCharacter)
{
}
