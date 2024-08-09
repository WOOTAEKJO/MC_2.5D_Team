#include "stdafx.h"
#include "..\Header\Drop1Attack.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "ObjCreationMgr.h"

#include "Rich.h"
#include "RichIDLE.h"
#include "Drop1Delay.h"

#include "RichPhase1IDLE.h"
#include "BossDropEffect.h"

CDrop1Attack::CDrop1Attack()
{
}

CDrop1Attack::~CDrop1Attack()
{
}

HRESULT CDrop1Attack::Ready_State(CCharacter* pCharacter)
{
	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	return S_OK;
}

CCharacterState* CDrop1Attack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (static_cast<CRich*>(pCharacter)->ETC_Is_Arrived(fTimeDelta)) {

		static_cast<CRich*>(pCharacter)->Create_Drop_Effect();
		static_cast<CRich*>(pCharacter)->ETC_ATTCOL();
		return CDrop1Delay::Create(pCharacter);
	}
	else {
		static_cast<CRich*>(pCharacter)->ETC_LookAT();
		static_cast<CRich*>(pCharacter)->ETC_Move(fTimeDelta, 50.f);
	}

	if (m_fCount > 5.f) {
		return CRichPhase1IDLE::Create(pCharacter);
	}

	return nullptr;
}

CDrop1Attack* CDrop1Attack::Create(CCharacter* pCharacter)
{
	CDrop1Attack* pInstance = new CDrop1Attack();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDrop1Attack::Free(CCharacter* pCharacter)
{
}
