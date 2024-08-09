#include "stdafx.h"
#include "..\Header\ShooterPowerReady.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "LeaderDelay.h"

#include "SwordMasterATTCol.h"

#include "Shooter.h"

#include "ShooterPowerAttack.h"
#include "ShooterAttack.h"

#include "Effect_Wind3.h"

CShooterPowerReady::CShooterPowerReady()
{
}

CShooterPowerReady::~CShooterPowerReady()
{
}

HRESULT CShooterPowerReady::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"SHOOTERPOWERREADY"));
	//static_cast<CShooter*>(pCharacter)->Create_Arrow();
	pCharacter->Set_Push_Check(true);
	pCharacter->Set_SkillRunnig(true);
	CObjCreationMgr::GetInstance()->Create_Effect<CEffect_Wind3>(*pCharacter->Get_Transform()->Get_Pos());
	
	return S_OK;
}

CCharacterState* CShooterPowerReady::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	Add_Count(fTimeDelta);

	if (m_fCount > 4.0f) {
		return CShooterPowerAttack::Create(pCharacter);
	}

	return nullptr;
}

CShooterPowerReady* CShooterPowerReady::Create(CCharacter* pCharacter)
{
	CShooterPowerReady* pInstance = new CShooterPowerReady();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShooterPowerReady::Free(CCharacter* pCharacter)
{
}
