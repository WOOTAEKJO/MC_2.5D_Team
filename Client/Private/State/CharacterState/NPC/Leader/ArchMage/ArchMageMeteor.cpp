#include "stdafx.h"
#include "..\Header\ArchMageMeteor.h"

#include "ObjCreationMgr.h"

#include "Export_Utility.h"
#include "Export_System.h"

#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "LeaderDelay.h"

#include "TestBullet3.h"
#include "Meteor_CubeItem.h"

#include "ArchMageAttack.h"

#include "Effect_Spear3.h"
#include "LeaderIDLE.h"

CArchMageMeteor::CArchMageMeteor()
{
}

CArchMageMeteor::~CArchMageMeteor()
{
}

HRESULT CArchMageMeteor::Ready_State(CCharacter* pCharacter)
{
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"METEORREADY"));
	pCharacter->Set_Push_Check(true);
	pCharacter->Set_SkillRunnig(true);
	

	CObjCreationMgr::GetInstance()->Create_Effect_Bottom<CEffect_Spear3>(pCharacter->Get_Transform());

	return S_OK;
}

CCharacterState* CArchMageMeteor::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (pCharacter->Get_Target() == nullptr) 
	{
		pCharacter->Set_FullCount(true);
		return CLeaderIDLE::Create(pCharacter);
		//return CArchMageMeteor::Create(pCharacter);
	}

	Add_Count(fTimeDelta);

	if (m_fCount > 3.f && pCharacter->Get_Target() != nullptr) {
		CObjCreationMgr::GetInstance()->Create_Bullet_Meteor_CubeItem<CMeteor_CubeItem>(pCharacter);
		pCharacter->Set_Push_Check(false);
		pCharacter->Set_SkillRunnig(false);
		pCharacter->Set_FullCount(false);
		return CLeaderDelay::Create(pCharacter, 3.f);
	}
	//if (m_fCount > 3.0f && m_fCount < 3.02f)
	//{
	//	
	//}

	pCharacter->Set_FullCount(true);

	return nullptr;
}

CArchMageMeteor* CArchMageMeteor::Create(CCharacter* pCharacter)
{
	CArchMageMeteor* pInstance = new CArchMageMeteor();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CArchMageMeteor::Free(CCharacter* pCharacter)
{
}
