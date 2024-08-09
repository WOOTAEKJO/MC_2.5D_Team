#include "stdafx.h"
#include "..\Header\LeaderDelay.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "LeaderIDLE.h"
#include "ShooterAttack.h"

CLeaderDelay::CLeaderDelay()
{
}

CLeaderDelay::~CLeaderDelay()
{
}

HRESULT CLeaderDelay::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANIDLE"));
	return S_OK;
}

CCharacterState* CLeaderDelay::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (pCharacter == nullptr)
		return nullptr;

	switch (pCharacter->Get_WeaponType())
	{
	case WEAPONTYPE::SWORD:
		break;
	case WEAPONTYPE::WAND:
		break;
	case WEAPONTYPE::CROSS:
		break;
	case WEAPONTYPE::BOW:
		break;
	default:
		break;
	}

	pCharacter->Target_Dir_Update();
	dynamic_cast<CHuman*>(pCharacter)->Update_Dir_To_Destination();

	if (Get_Count() > m_fDelTime) {
		return CLeaderIDLE::Create(pCharacter);
	}

	return nullptr;
}

CLeaderDelay* CLeaderDelay::Create(CCharacter* pCharacter, const _float& fDelTime)
{
	CLeaderDelay* pInstance = new CLeaderDelay();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}
	pInstance->Set_DelTime(fDelTime);

	return pInstance;
}

void CLeaderDelay::Free(CCharacter* pCharacter)
{
}
