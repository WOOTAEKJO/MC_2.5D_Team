#include "stdafx.h"
#include "..\Header\ShooterPowerAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "LeaderDelay.h"

#include "SwordMasterATTCol.h"

#include "Shooter.h"

#include "LeaderDelay.h"
#include "ShooterAttack.h"

CShooterPowerAttack::CShooterPowerAttack()
{
}

CShooterPowerAttack::~CShooterPowerAttack()
{
}

HRESULT CShooterPowerAttack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"SHOOTERPOWERATTACK2"));
	//static_cast<CShooter*>(pCharacter)->Create_Arrow();
	return S_OK;
}

CCharacterState* CShooterPowerAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End()) {
		pCharacter->Set_Push_Check(false);
		pCharacter->Set_SkillRunnig(false);
		pCharacter->Set_FullCount(false);
		return CShooterAttack::Create(pCharacter);
	}

	return nullptr;
}

CShooterPowerAttack* CShooterPowerAttack::Create(CCharacter* pCharacter)
{
	CShooterPowerAttack* pInstance = new CShooterPowerAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShooterPowerAttack::Free(CCharacter* pCharacter)
{
}
