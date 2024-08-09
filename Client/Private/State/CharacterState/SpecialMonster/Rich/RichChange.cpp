#include "stdafx.h"
#include "..\Header\RichChange.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "RichPattern1Look.h"
#include "RichGroggy.h"

#include "LaserAttackSC.h"
#include "RichPhase1IDLE.h"

#include "Rich.h"
#include "SoundMgr.h"

CRichChange::CRichChange()
{
}

CRichChange::~CRichChange()
{
}

HRESULT CRichChange::Ready_State(CCharacter* pCharacter)
{

	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHLASER"));

	CSoundManager::GetInstance()->StopAll();
	CSoundManager::GetInstance()->PlaySound(L"Devil2.ogg", CHANNELID::SOUND_BOSS_VOICE, 2.f);
	CSoundManager::GetInstance()->PlayBGM(L"The_Four_Horsemen.mp3", 1.f);
	
	return S_OK;
}

CCharacterState* CRichChange::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_fCount > 1.5f) {
		static_cast<CRich*>(pCharacter)->Change_Tex();
	}

	if (m_fCount > 3.f) {
		static_cast<CRich*>(pCharacter)->Set_PhaseChangeCheck(false);
		return CRichPhase1IDLE::Create(pCharacter);
	}

	return nullptr;
}

CRichChange* CRichChange::Create(CCharacter* pCharacter)
{
	CRichChange* pInstance = new CRichChange();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichChange::Free(CCharacter* pCharacter)
{
}
