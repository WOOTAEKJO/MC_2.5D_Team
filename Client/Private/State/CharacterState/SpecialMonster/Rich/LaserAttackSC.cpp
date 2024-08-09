#include "stdafx.h"
#include "..\Header\LaserAttackSC.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "SoundMgr.h"
#include "RichPattern1Look.h"
#include "RichGroggy.h"

#include "ObjCreationMgr.h"

#include "LaserAttackTE.h"

#include "Rich.h"
#include "MeleeATTCol.h"

CLaserAttackSC::CLaserAttackSC()
{
}

CLaserAttackSC::~CLaserAttackSC()
{
}

HRESULT CLaserAttackSC::Ready_State(CCharacter* pCharacter)
{

	if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE1) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	}
	else if (static_cast<CRich*>(pCharacter)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
		static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHLASER"));
	}
	static_cast<CRich*>(pCharacter)->Laser_Create(CRich::RICHLASERTYPE::CROSS);
	static_cast<CRich*>(pCharacter)->LaserRange_Create(CRich::RICHLASERTYPE::EX);

	//CSoundManager::GetInstance()->StopAll();
	CSoundManager::GetInstance()->StopSound(CHANNELID::SOUND_BOSS_VOICE);
	CSoundManager::GetInstance()->PlaySound(L"Darkness5.ogg", CHANNELID::SOUND_BOSS_VOICE, 2.f);
	//CSoundManager::GetInstance()->PlayBGM(L"The_Four_Horsemen.mp3", 1.f);
	//CObjCreationMgr::GetInstance()->Create_ATTColl<CMeleeATTCol>(100.f, _vec3(50.f, 40.f, 50.f), 3.f, 9999.f, OBJECTTYPE::ALLY_BULLET, pCharacter);

	return S_OK;
}

CCharacterState* CLaserAttackSC::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	//

	//if (static_cast<CRich*>(pCharacter)->Is_Laser_Animation_End()) {

		Add_Count(fTimeDelta);
		if (m_fCount > 1.5f) {
			static_cast<CRich*>(pCharacter)->Delete_LaserRange();
			return CLaserAttackTE::Create(pCharacter);
			
		}
	//}

	return nullptr;
}

CLaserAttackSC* CLaserAttackSC::Create(CCharacter* pCharacter)
{
	CLaserAttackSC* pInstance = new CLaserAttackSC();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLaserAttackSC::Free(CCharacter* pCharacter)
{
}
