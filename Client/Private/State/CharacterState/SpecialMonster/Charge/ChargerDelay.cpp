#include "stdafx.h"
#include "..\Header\ChargerDelay.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "ChargerIDLE.h"


CChargerDelay::CChargerDelay()
{
}

CChargerDelay::~CChargerDelay()
{
}

HRESULT CChargerDelay::Ready_State(CCharacter* pCharacter)
{
	pCharacter->Set_IsRotate(false);
	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"CHARGERBASIC"));
	return S_OK;
}

CCharacterState* CChargerDelay::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (pCharacter == nullptr)
		return nullptr;

	if (Get_Count() > m_fDelTime) {
		pCharacter->Target_Dir_Update();
		static_cast<CMonster*>(pCharacter)->Update_Dir_To_Destination();
		pCharacter->Set_AttackRange(8.f);
		pCharacter->LookAt_Target();
		return CChargerIDLE::Create(pCharacter);
	}

	return nullptr;
}

CChargerDelay* CChargerDelay::Create(CCharacter* pCharacter,const _float& fDelTime)
{
	CChargerDelay* pInstance = new CChargerDelay();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	pInstance->Set_DelTime(fDelTime);

	return pInstance;
}

void CChargerDelay::Free(CCharacter* pCharacter)
{
}
