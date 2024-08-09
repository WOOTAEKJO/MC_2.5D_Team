#include "stdafx.h"
#include "..\Header\RichLaserReady.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "RichPattern1Look.h"
#include "RichGroggy.h"

#include "LaserAttackSC.h"

#include "Rich.h"

CRichLaserReady::CRichLaserReady()
{
}

CRichLaserReady::~CRichLaserReady()
{
}

HRESULT CRichLaserReady::Ready_State(CCharacter* pCharacter)
{

	
	if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE1) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	}
	else if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHLASER"));
	}
	static_cast<CRich*>(pCharacter)->LaserRange_Create(CRich::RICHLASERTYPE::CROSS);

	return S_OK;
}

CCharacterState* CRichLaserReady::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_fCount > 1.5f) {
		static_cast<CRich*>(pCharacter)->Delete_LaserRange();
		return CLaserAttackSC::Create(pCharacter);
	}

	return nullptr;
}

CRichLaserReady* CRichLaserReady::Create(CCharacter* pCharacter)
{
	CRichLaserReady* pInstance = new CRichLaserReady();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichLaserReady::Free(CCharacter* pCharacter)
{
}
