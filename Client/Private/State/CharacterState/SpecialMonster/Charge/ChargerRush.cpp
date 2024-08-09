#include "stdafx.h"
#include "..\Header\ChargerRush.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "ChargerAttack.h"
#include "ChargerDelay.h"

CChargerRush::CChargerRush()
{
}

CChargerRush::~CChargerRush()
{
}

HRESULT CChargerRush::Ready_State(CCharacter* pCharacter)
{
	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"CHARGERRUSH"));
	
	pCharacter->Set_Speed(20.f);
	return S_OK;
}

CCharacterState* CChargerRush::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (pCharacter->Is_Target_Dead()) {
		pCharacter->Reset_Speed();
		return CChargerDelay::Create(pCharacter,3.f);
	}
	if (static_cast<CMonster*>(pCharacter)->Attack_Stance(5.0f)) {
		pCharacter->Reset_Speed();
		return CChargerAttack::Create(pCharacter);
	}

	pCharacter->Move(fTimeDelta);

	return nullptr;
}

CChargerRush* CChargerRush::Create(CCharacter* pCharacter)
{
	CChargerRush* pInstance = new CChargerRush();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CChargerRush::Free(CCharacter* pCharacter)
{
}
