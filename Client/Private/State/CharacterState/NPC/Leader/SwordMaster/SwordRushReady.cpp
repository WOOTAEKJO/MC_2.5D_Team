#include "stdafx.h"
#include "..\Header\SwordRushReady.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"

#include "HNPCDelay.h"
#include "SwordRushAttack.h"

#include "ObjCreationMgr.h"
#include "Effect_Sword8.h"


CSwordRushReady::CSwordRushReady()
{
}

CSwordRushReady::~CSwordRushReady()
{
}

HRESULT CSwordRushReady::Ready_State(CCharacter* pCharacter)
{
	//pCharacter->Set_InitLook();	// �ִϸ��̼��� ���ư��� ���� �� ������ ����
	static_cast<CHuman*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"SWORDRUSHREADY"));
	//pCharacter->Add_SubWeapon(WEAPONTYPE::BOW);	// ȭ�� ����
	//pCharacter->Set_IsRotate(true); // �ڵ����� ���ư��� ����
	pCharacter->Set_Push_Check(true);
	pCharacter->Set_SkillRunnig(true);

	CObjCreationMgr::GetInstance()->Create_Effect_Bottom<CEffect_Sword8>(pCharacter->Get_Transform());


	return S_OK;
}

CCharacterState* CSwordRushReady::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_fCount > 2.f)
	{
		return CSwordRushAttack::Create(pCharacter);
	}
	return nullptr;
}

CSwordRushReady* CSwordRushReady::Create(CCharacter* pCharacter)
{
	CSwordRushReady* pInstance = new CSwordRushReady();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSwordRushReady::Free(CCharacter* pCharacter)
{
}
