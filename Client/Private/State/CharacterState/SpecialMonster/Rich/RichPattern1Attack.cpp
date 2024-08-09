#include "stdafx.h"
#include "..\Header\RichPattern1Attack.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "Rich.h"
#include "RichIDLE.h"
#include "RichPattern1Delay.h"

CRichPattern1Attack::CRichPattern1Attack()
{
}

CRichPattern1Attack::~CRichPattern1Attack()
{
}

HRESULT CRichPattern1Attack::Ready_State(CCharacter* pCharacter)
{
	if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE1) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	}
	else if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHDROP"));
	}
	return S_OK;
}

CCharacterState* CRichPattern1Attack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	/*if (static_cast<CMonster*>(pCharacter)->Get_ETCControl() == false) {
		return CRichIDLE::Create(pCharacter);
	}
	else {
		static_cast<CRich*>(pCharacter)->ETC_LookAT();
		static_cast<CRich*>(pCharacter)->ETC_Move(fTimeDelta, 50.f);
		static_cast<CRich*>(pCharacter)->ETC_Is_Arrived(fTimeDelta);
	}*/

	if (static_cast<CRich*>(pCharacter)->ETC_Is_Arrived(fTimeDelta)) {

		static_cast<CRich*>(pCharacter)->Create_Drop_Effect();
		static_cast<CRich*>(pCharacter)->ETC_ATTCOL();
		return CRichPattern1Delay::Create(pCharacter);
	}
	else {
		static_cast<CRich*>(pCharacter)->ETC_LookAT();
		static_cast<CRich*>(pCharacter)->ETC_Move(fTimeDelta, 50.f);
	}

	return nullptr;
}

CRichPattern1Attack* CRichPattern1Attack::Create(CCharacter* pCharacter)
{
	CRichPattern1Attack* pInstance = new CRichPattern1Attack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichPattern1Attack::Free(CCharacter* pCharacter)
{
}
