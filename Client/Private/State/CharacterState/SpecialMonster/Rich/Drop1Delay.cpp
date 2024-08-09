#include "stdafx.h"
#include "..\Header\Drop1Delay.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "RichPhase1IDLE.h"

#include "Rich.h"

CDrop1Delay::CDrop1Delay()
{
}

CDrop1Delay::~CDrop1Delay()
{
}

HRESULT CDrop1Delay::Ready_State(CCharacter* pCharacter)
{
	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHIDLE"));
	return S_OK;
}

CCharacterState* CDrop1Delay::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_fCount > 1.f) {
		static_cast<CMonster*>(pCharacter)->Set_ETCControl(false);
		static_cast<CRich*>(pCharacter)->Delete_ETC_Attack_Range();
		return CRichPhase1IDLE::Create(pCharacter);
	}

	return nullptr;
}

CDrop1Delay* CDrop1Delay::Create(CCharacter* pCharacter)
{
	CDrop1Delay* pInstance = new CDrop1Delay();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDrop1Delay::Free(CCharacter* pCharacter)
{
}
