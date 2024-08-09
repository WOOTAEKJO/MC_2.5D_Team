#include "stdafx.h"
#include "..\Header\ChargerAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "ChargerDelay.h"

#include "ObjCreationMgr.h"
#include "BlowATTCol.h"

CChargerAttack::CChargerAttack()
{
}

CChargerAttack::~CChargerAttack()
{
}

HRESULT CChargerAttack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"CHARGERATTACK"));
	pCharacter->Set_IsRotate(true);
	//pCharacter->Create_ATTColl(0.3f, _vec3(1.3f, 1.3f, 1.3f), 3.f, OBJECTTYPE::MONSTER_BULLET, pCharacter);
	CObjCreationMgr::GetInstance()->Create_ATTColl<CBlowATTCol>(0.3f, _vec3(1.6f, 1.6f, 1.6f), 3.f, 5.f, OBJECTTYPE::MONSTER_BULLET, pCharacter);
	return S_OK;
}

CCharacterState* CChargerAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (static_cast<CMonster*>(pCharacter)->Is_Animation_Frame_End()) {
		return CChargerDelay::Create(pCharacter,3.f);
	}

	return nullptr;
}

CChargerAttack* CChargerAttack::Create(CCharacter* pCharacter)
{
	CChargerAttack* pInstance = new CChargerAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CChargerAttack::Free(CCharacter* pCharacter)
{
}
