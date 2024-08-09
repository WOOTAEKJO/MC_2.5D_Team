#include "stdafx.h"
#include "..\Header\DanceStart.h"

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

CDanceStart::CDanceStart()
{
}

CDanceStart::~CDanceStart()
{
}

HRESULT CDanceStart::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"DANCE"));


	return S_OK;
}

CCharacterState* CDanceStart::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	

	return nullptr;
}

CDanceStart* CDanceStart::Create(CCharacter* pCharacter)
{
	CDanceStart* pInstance = new CDanceStart();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDanceStart::Free(CCharacter* pCharacter)
{
}
