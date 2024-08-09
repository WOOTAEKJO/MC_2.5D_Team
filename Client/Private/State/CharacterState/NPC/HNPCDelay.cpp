#include "stdafx.h"
#include "..\Header\HNPCDelay.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HNPCIDLE.h"

CHNPCDelay::CHNPCDelay()
{
}

CHNPCDelay::~CHNPCDelay()
{
}

HRESULT CHNPCDelay::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANIDLE"));
	//pCharacter->Set_Push_Check(true);
	return S_OK;
}

CCharacterState* CHNPCDelay::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (pCharacter == nullptr)
		return nullptr;

	switch (pCharacter->Get_WeaponType())
	{
	case WEAPONTYPE::SWORD:
		break;
	case WEAPONTYPE::BOW:
		pCharacter->Set_IsRotate(false); // 자동으로 돌아가기 해제1
		break;
	case WEAPONTYPE::WAND:
		break;
	default:
		break;
	}

	pCharacter->Target_Dir_Update();
	dynamic_cast<CHuman*>(pCharacter)->Update_Dir_To_Destination();

	if (Get_Count() > m_fDelTime) {
		return CHNPCIDLE::Create(pCharacter);
	}

	return nullptr;
}

CHNPCDelay* CHNPCDelay::Create(CCharacter* pCharacter, const _float& fDelTime)
{
	CHNPCDelay* pInstance = new CHNPCDelay();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}
	pInstance->Set_DelTime(fDelTime);

	return pInstance;
}

void CHNPCDelay::Free(CCharacter* pCharacter)
{
}
