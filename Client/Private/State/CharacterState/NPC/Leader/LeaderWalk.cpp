#include "stdafx.h"
#include "..\Header\LeaderWalk.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "LeaderIDLE.h"
#include "SwordRushReady.h"
#include "SwordMasterAttack.h"
#include "BladeAttack.h"

#include "ArchMageAttack.h"
#include "ArchMageMeteor.h"

#include "HighPriestRangeAttack.h"

#include "ShooterAttack.h"
#include "ShooterPowerReady.h"

#include "ShooterPowerAttack.h"

#include "DanceReady.h"

CLeaderWalk::CLeaderWalk()
{
}

CLeaderWalk::~CLeaderWalk()
{
}

HRESULT CLeaderWalk::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANWALK"));

	return S_OK;
}

CCharacterState* CLeaderWalk::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (Engine::Key_Down(DIK_N)) {
		return CDanceReady::Create(pCharacter);
	}

	switch (pCharacter->Get_WeaponType())
	{
	case WEAPONTYPE::SWORD:
		if (static_cast<CHuman*>(pCharacter)->Attack_Stance(5.f)) {
			if (static_cast<CHuman*>(pCharacter)->Get_FullCount()) {
				return CBladeAttack::Create(pCharacter);
			}
			return CSwordMasterAttack::Create(pCharacter);
		}
		else if (static_cast<CHuman*>(pCharacter)->Attack_Stance(30.f)) {
			if (static_cast<CHuman*>(pCharacter)->Get_FullCount()) {
				return CBladeAttack::Create(pCharacter);
			}
			return CSwordRushReady::Create(pCharacter);
		}

		break;
	case WEAPONTYPE::WAND:

		if (static_cast<CHuman*>(pCharacter)->Attack_Stance(30.f)) {
			if (static_cast<CHuman*>(pCharacter)->Get_FullCount()) {
				return CArchMageMeteor::Create(pCharacter);
			}

			return CArchMageAttack::Create(pCharacter);
		}

		break;
	case WEAPONTYPE::CROSS:

		if (static_cast<CHuman*>(pCharacter)->Attack_Stance(5.f)) {
			if (static_cast<CHuman*>(pCharacter)->Get_FullCount()) {
				return CHighPriestRangeAttack::Create(pCharacter);
			}
		}

		break;
	case WEAPONTYPE::BOW:

		if (static_cast<CHuman*>(pCharacter)->Attack_Stance(20.f)) {
			/*if (static_cast<CHuman*>(pCharacter)->Get_FullCount()) {
				return CShooterPowerReady::Create(pCharacter);
			}*/
			return CShooterPowerReady::Create(pCharacter);
			//return CShooterAttack::Create(pCharacter);
		}
		/*if (Engine::Key_Down(DIK_F6)) {
			return CShooterAttack::Create(pCharacter);
		}*/

		break;
	default:
		break;
	}


	if (pCharacter->Is_Arrived()) {
		return CLeaderIDLE::Create(pCharacter);
	}

	pCharacter->Move(fTimeDelta);

	return nullptr;
}

CLeaderWalk* CLeaderWalk::Create(CCharacter* pCharacter)
{
	CLeaderWalk* pInstance = new CLeaderWalk();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLeaderWalk::Free(CCharacter* pCharacter)
{
}
