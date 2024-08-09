#include "stdafx.h"
#include "..\Header\HNPCIDLE.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HNPCSwordAttack.h"
#include "HNPCBowReady.h"
#include "HNPCMageReady.h"
#include "HNPCShieldBlock.h"
#include "HNPCPriestHeal.h"
#include "HNPCWalk.h"

#include "DanceReady.h"

CHNPCIDLE::CHNPCIDLE()
{
}

CHNPCIDLE::~CHNPCIDLE()
{
}

HRESULT CHNPCIDLE::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANIDLE"));
	//pCharacter->Set_Push_Check(true);

	return S_OK;
}

CCharacterState* CHNPCIDLE::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (static_cast<CHuman*>(pCharacter)->Get_Dance()) {
		return CDanceReady::Create(pCharacter);
	}

	if (!pCharacter->Get_MoveMode())
	{
		switch (pCharacter->Get_WeaponType())
		{
		case WEAPONTYPE::SWORD:
			if (static_cast<CHuman*>(pCharacter)->Attack_Stance(3.7f)) {
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

			if (static_cast<CHuman*>(pCharacter)->Attack_Stance(5.f)) {
				return CHNPCShieldBlock::Create(pCharacter);
			}

			break;
		case WEAPONTYPE::CROSS:

			if (static_cast<CHuman*>(pCharacter)->Attack_Stance(10.f)) {
				return CHNPCPriestHeal::Create(pCharacter);
			}

			break;
		default:
			break;
		}
	}
	

	if (!pCharacter->Is_Arrived()) {
		return CHNPCWalk::Create(pCharacter);
	}

	return nullptr;
}

CHNPCIDLE* CHNPCIDLE::Create(CCharacter* pCharacter)
{
	CHNPCIDLE* pInstance = new CHNPCIDLE();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHNPCIDLE::Free(CCharacter* pCharacter)
{
}
