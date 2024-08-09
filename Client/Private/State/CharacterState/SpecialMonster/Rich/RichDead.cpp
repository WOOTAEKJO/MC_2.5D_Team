#include "stdafx.h"
#include "..\Header\RichDead.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "RichPattern1Look.h"

#include "Drop1Look.h"

#include "Rich.h"
#include "RichPhase1.h"

CRichDead::CRichDead()
{
}

CRichDead::~CRichDead()
{
}

HRESULT CRichDead::Ready_State(CCharacter* pCharacter)
{

	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHDEAD"));

	return S_OK;
}

CCharacterState* CRichDead::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	//Add_Count(fTimeDelta);

	if (static_cast<CRich*>(pCharacter)->Is_Animation_Frame_End()) {
		pCharacter->Set_Dead();
	}

	return nullptr;
}

CRichDead* CRichDead::Create(CCharacter* pCharacter)
{
	CRichDead* pInstance = new CRichDead();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichDead::Free(CCharacter* pCharacter)
{
}
