#include "stdafx.h"
#include "..\Header\DanceReady.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "LeaderWalk.h"
#include "SwordRushReady.h"
#include "SwordMasterAttack.h"
#include "BladeAttack.h"

#include "ArchMageAttack.h"
#include "ArchMageMeteor.h"

#include "HighPriestRangeAttack.h"

#include "ShooterAttack.h"
#include "ShooterPowerReady.h"
#include "ShooterPowerAttack.h"
#include "DanceStart.h"

CDanceReady::CDanceReady()
{
}

CDanceReady::~CDanceReady()
{
}

HRESULT CDanceReady::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"DANCEREADY"));


	return S_OK;
}

CCharacterState* CDanceReady::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);
	if (m_fCount>4.f) {
		return CDanceStart::Create(pCharacter);
	}

	return nullptr;
}

CDanceReady* CDanceReady::Create(CCharacter* pCharacter)
{
	CDanceReady* pInstance = new CDanceReady();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDanceReady::Free(CCharacter* pCharacter)
{
}
