#include "stdafx.h"
#include "..\Header\LaserAttackTC.h"

#include "Export_System.h"

#include "SoundMgr.h"
#include "SaveLoadMgr.h"
#include "RichPattern1Look.h"
#include "RichGroggy.h"

#include "RichLaserDelay.h"
#include "LaserAttackFE.h"

#include "Rich.h"

CLaserAttackTC::CLaserAttackTC()
{
}

CLaserAttackTC::~CLaserAttackTC()
{
}

HRESULT CLaserAttackTC::Ready_State(CCharacter* pCharacter)
{

	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHLASER"));
	static_cast<CRich*>(pCharacter)->Laser_Create(CRich::RICHLASERTYPE::CROSS);
	static_cast<CRich*>(pCharacter)->LaserRange_Create(CRich::RICHLASERTYPE::EX);

	//CSoundManager::GetInstance()->StopAll();
	CSoundManager::GetInstance()->StopSound(CHANNELID::SOUND_BOSS_VOICE);
	CSoundManager::GetInstance()->PlaySound(L"Darkness5.ogg", CHANNELID::SOUND_BOSS_VOICE, 2.f);
	//CSoundManager::GetInstance()->PlayBGM(L"The_Four_Horsemen.mp3", 1.f);

	return S_OK;
}

CCharacterState* CLaserAttackTC::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	//Add_Count(fTimeDelta);
	//if (static_cast<CRich*>(pCharacter)->Is_Laser_Animation_End()) {
		Add_Count(fTimeDelta);
		if (m_fCount > 1.5f) {
			static_cast<CRich*>(pCharacter)->Delete_LaserRange();
			return CLaserAttackFE::Create(pCharacter);
		}
	//}

	return nullptr;
}

CLaserAttackTC* CLaserAttackTC::Create(CCharacter* pCharacter)
{
	CLaserAttackTC* pInstance = new CLaserAttackTC();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLaserAttackTC::Free(CCharacter* pCharacter)
{
}
