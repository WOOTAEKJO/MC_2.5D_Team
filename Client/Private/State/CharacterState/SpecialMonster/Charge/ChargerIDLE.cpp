#include "stdafx.h"
#include "..\Header\ChargerIDLE.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "ChargerRush.h"
#include "ChargerWalk.h"
#include "ChargerAttack.h"

CChargerIDLE::CChargerIDLE()
{
}

CChargerIDLE::~CChargerIDLE()
{
}

HRESULT CChargerIDLE::Ready_State(CCharacter* pCharacter)
{
	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"CHARGERBASIC"));
	return S_OK;
}

CCharacterState* CChargerIDLE::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	if (pCharacter->Is_Target_Dead()) {
		pCharacter->Set_AttackRange(20.f);
		pCharacter->LookAt_Target();
		if (!pCharacter->Is_Target_Dead()) {
			return CChargerRush::Create(pCharacter);
		}else if (!pCharacter->Is_Arrived()) {
			return CChargerWalk::Create(pCharacter);
		}
	}
	else {
		if (!pCharacter->Is_Arrived()) {
			return CChargerWalk::Create(pCharacter);
		}
		else if (static_cast<CMonster*>(pCharacter)->Attack_Stance(3.f)) {
			return CChargerAttack::Create(pCharacter);
		}
	}

	return nullptr;
}

CChargerIDLE* CChargerIDLE::Create(CCharacter* pCharacter)
{
	CChargerIDLE* pInstance = new CChargerIDLE();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CChargerIDLE::Free(CCharacter* pCharacter)
{
}
