#include "stdafx.h"
#include "..\Header\HNPCWalk.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HNPCSwordAttack.h"
#include "HNPCBowReady.h"
#include "HNPCMageReady.h"
#include "HNPCShieldBlock.h"
#include "HNPCPriestHeal.h"
#include "HNPCIDLE.h"

CHNPCWalk::CHNPCWalk()
{
}

CHNPCWalk::~CHNPCWalk()
{
}

HRESULT CHNPCWalk::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANWALK"));
	//pCharacter->Set_Push_Check(false);
	return S_OK;
}

CCharacterState* CHNPCWalk::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (!pCharacter->Get_MoveMode()) 
	{
		switch (pCharacter->Get_WeaponType())
		{
		case WEAPONTYPE::SWORD:
			if (static_cast<CHuman*>(pCharacter)->Attack_Stance(4.f)) {
				return CHNPCSwordAttack::Create(pCharacter);
			}

			break;
		case WEAPONTYPE::BOW:

			if (static_cast<CHuman*>(pCharacter)->Attack_Stance(20.f)) {
				return CHNPCBowReady::Create(pCharacter);
			}

			break;
		case WEAPONTYPE::WAND:

			if (static_cast<CHuman*>(pCharacter)->Attack_Stance(30.f)) {
				return CHNPCMageReady::Create(pCharacter);
			}

			break;
		case WEAPONTYPE::SHIELD:

			if (static_cast<CHuman*>(pCharacter)->Attack_Stance(2.7f)) {
				return CHNPCShieldBlock::Create(pCharacter);
			}

			break;
		case WEAPONTYPE::CROSS:

			if (static_cast<CHuman*>(pCharacter)->Attack_Stance(20.f)) {
				return CHNPCPriestHeal::Create(pCharacter);
			}

			break;
		default:
			break;
		}
	}

	
	if (pCharacter->Is_Arrived()) {
		return CHNPCIDLE::Create(pCharacter);
	}

	pCharacter->Move(fTimeDelta);

	return nullptr;
}

CHNPCWalk* CHNPCWalk::Create(CCharacter* pCharacter)
{
	CHNPCWalk* pInstance = new CHNPCWalk();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHNPCWalk::Free(CCharacter* pCharacter)
{
}
