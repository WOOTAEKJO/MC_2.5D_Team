#include "stdafx.h"
#include "..\Header\SwordRushAttack.h"

#include "ObjCreationMgr.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "LeaderDelay.h"

#include "SwordMasterRushATTCol.h"


CSwordRushAttack::CSwordRushAttack()
{
}

CSwordRushAttack::~CSwordRushAttack()
{
}

HRESULT CSwordRushAttack::Ready_State(CCharacter* pCharacter)
{
	//pCharacter->Set_InitLook();	// 애니메이션이 돌아가기 전에 룩 방향을 저장
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"SWORDRUSHATTACK"));
	//pCharacter->Add_SubWeapon(WEAPONTYPE::BOW);	// 화살 생성
	//pCharacter->Set_IsRotate(true); // 자동으로 돌아가기 해제
	CObjCreationMgr::GetInstance()->Create_ATTColl<CSwordMasterRushATTCol>(0.2f, _vec3(5.f, 5.f, 5.f), 0.f, 20.f, OBJECTTYPE::ALLY_BULLET, pCharacter);
	pCharacter->Set_FullCount(false);

	return S_OK;
}

CCharacterState* CSwordRushAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_fCount > 0.05f) {
		CObjCreationMgr::GetInstance()->Create_ATTColl<CSwordMasterRushATTCol>(0.2f, _vec3(5.f, 5.f, 5.f), 0.f, 10.f, OBJECTTYPE::ALLY_BULLET, pCharacter);
		m_fCount = 0.f;
	}

	if (pCharacter->Is_Arrived()) {
		pCharacter->Set_Push_Check(false);
		pCharacter->Set_SkillRunnig(false);
		return CLeaderDelay::Create(pCharacter, 2.f);
	}

	pCharacter->Rush_Move(fTimeDelta, 30.f);
	return nullptr;
}

CSwordRushAttack* CSwordRushAttack::Create(CCharacter* pCharacter)
{
	CSwordRushAttack* pInstance = new CSwordRushAttack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSwordRushAttack::Free(CCharacter* pCharacter)
{
}
