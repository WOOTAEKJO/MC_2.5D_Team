#include "stdafx.h"
#include "..\Header\BladeAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "LeaderDelay.h"


CBladeAttack::CBladeAttack()
{
}

CBladeAttack::~CBladeAttack()
{
}

HRESULT CBladeAttack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"BLADEATTACK"));
	//pCharacter->Create_ATTColl(0.3f, _vec3(1.5f, 1.5f, 1.5f), 2.f, OBJECTTYPE::ALLY_BULLET, pCharacter);
	return S_OK;
}

CCharacterState* CBladeAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	CHuman* human = static_cast<CHuman*>(pCharacter);
	if (human->Is_Animation_Frame_End()) {

		human->Set_FullCount(false);
		return CLeaderDelay::Create(pCharacter, 1.f);
	}
	return nullptr;
}

CBladeAttack* CBladeAttack::Create(CCharacter* pCharacter)
{
	CBladeAttack* pInstance = new CBladeAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBladeAttack::Free(CCharacter* pCharacter)
{
}
