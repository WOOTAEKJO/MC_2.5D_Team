#include "stdafx.h"
#include "..\Header\ShooterAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "LeaderDelay.h"

#include "SwordMasterATTCol.h"

#include "Shooter.h"

#include "Effect_Wind3_Flower.h"

CShooterAttack::CShooterAttack()
{
}

CShooterAttack::~CShooterAttack()
{
}

HRESULT CShooterAttack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"SHOOTERATTACK"));
	static_cast<CShooter*>(pCharacter)->Create_Arrow_Multi();
	CObjCreationMgr::GetInstance()->Create_Effect_Bottom<CEffect_Wind3_Flower>(pCharacter->Get_Transform());
	return S_OK;
}

CCharacterState* CShooterAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	if (static_cast<CHuman*>(pCharacter)->Is_Animation_Frame_End()) {
		if (static_cast<CShooter*>(pCharacter)->Get_Attack_Count() < 6) {
			static_cast<CShooter*>(pCharacter)->One_Attack_Count();
			return CShooterAttack::Create(pCharacter);
		}
		else {
			static_cast<CShooter*>(pCharacter)->Reset_Attack_Count();
			return CLeaderDelay::Create(pCharacter, 1.5f);
		}
	}
	
	return nullptr;
}

CShooterAttack* CShooterAttack::Create(CCharacter* pCharacter)
{
	CShooterAttack* pInstance = new CShooterAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShooterAttack::Free(CCharacter* pCharacter)
{
}
