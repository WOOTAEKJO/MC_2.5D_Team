#include "stdafx.h"
#include "..\Header\LaserAttackTE.h"

#include "Export_System.h"

#include "SoundMgr.h"
#include "SaveLoadMgr.h"
#include "RichPattern1Look.h"
#include "RichGroggy.h"

#include "LaserAttackTC.h"

#include "RichLaserDelay.h"

#include "Rich.h"

CLaserAttackTE::CLaserAttackTE()
{
}

CLaserAttackTE::~CLaserAttackTE()
{
}

HRESULT CLaserAttackTE::Ready_State(CCharacter* pCharacter)
{

	if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE1) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	}
	else if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHLASER"));
	}
	static_cast<CRich*>(pCharacter)->Laser_Create(CRich::RICHLASERTYPE::EX);
	if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
		static_cast<CRich*>(pCharacter)->LaserRange_Create(CRich::RICHLASERTYPE::CROSS);
	}

	//CSoundManager::GetInstance()->StopAll();
	CSoundManager::GetInstance()->StopSound(CHANNELID::SOUND_BOSS_VOICE);
	CSoundManager::GetInstance()->PlaySound(L"Darkness5.ogg", CHANNELID::SOUND_BOSS_VOICE, 2.f);
	//CSoundManager::GetInstance()->PlayBGM(L"The_Four_Horsemen.mp3", 1.f);
	return S_OK;
}

CCharacterState* CLaserAttackTE::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	//Add_Count(fTimeDelta);

	//if (static_cast<CRich*>(pCharacter)->Is_Laser_Animation_End()) {
		Add_Count(fTimeDelta);
		if (m_fCount > 1.5f) {
			static_cast<CRich*>(pCharacter)->Delete_LaserRange();
			if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE1) {
				return CRichLaserDelay::Create(pCharacter);
			}
			else if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
				return CLaserAttackTC::Create(pCharacter);
			}
		}
	//}

	return nullptr;
}

CLaserAttackTE* CLaserAttackTE::Create(CCharacter* pCharacter)
{
	CLaserAttackTE* pInstance = new CLaserAttackTE();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLaserAttackTE::Free(CCharacter* pCharacter)
{
}
