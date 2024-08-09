#include "stdafx.h"
#include "..\Header\ShooterDelay.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "LeaderDelay.h"

#include "SwordMasterATTCol.h"

#include "Shooter.h"

CShooterDelay::CShooterDelay()
{
}

CShooterDelay::~CShooterDelay()
{
}

HRESULT CShooterDelay::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"SHOOTERATTACK"));
	//static_cast<CShooter*>(pCharacter)->Create_Arrow();
	return S_OK;
}

CCharacterState* CShooterDelay::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	/*if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End()) {
		if (static_cast<CShooter*>(pCharacter)->Get_Attack_Count() < 2) {
			static_cast<CShooter*>(pCharacter)->One_Attack_Count();
			return CShooterDelay::Create(pCharacter);
		}
		else {
			static_cast<CShooter*>(pCharacter)->Reset_Attack_Count();
			return CLeaderDelay::Create(pCharacter, 0.5f);
		}
	}*/

	return nullptr;
}

CShooterDelay* CShooterDelay::Create(CCharacter* pCharacter)
{
	CShooterDelay* pInstance = new CShooterDelay();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShooterDelay::Free(CCharacter* pCharacter)
{
}
