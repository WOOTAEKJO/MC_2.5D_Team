#include "stdafx.h"
#include "..\Header\ChargerWalk.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "ChargerIDLE.h"
#include "ChargerAttack.h"
#include "ChargerRush.h"

CChargerWalk::CChargerWalk()
{
}

CChargerWalk::~CChargerWalk()
{
}

HRESULT CChargerWalk::Ready_State(CCharacter* pCharacter)
{
	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"CHARGERWALK"));
	return S_OK;
}

CCharacterState* CChargerWalk::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (static_cast<CMonster*>(pCharacter)->Attack_Stance(5.0f)) {
		return CChargerAttack::Create(pCharacter);
	}

	if(pCharacter->Is_Target_Dead()) {
		pCharacter->Set_AttackRange(30.f);
		pCharacter->LookAt_Target();
		if (!pCharacter->Is_Target_Dead()) {
			return CChargerRush::Create(pCharacter);
		}
	}

	if (pCharacter->Is_Arrived()) {
		return CChargerIDLE::Create(pCharacter);
	}

	pCharacter->Move(fTimeDelta);

	return nullptr;
}

CChargerWalk* CChargerWalk::Create(CCharacter* pCharacter)
{
	CChargerWalk* pInstance = new CChargerWalk();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CChargerWalk::Free(CCharacter* pCharacter)
{
}
