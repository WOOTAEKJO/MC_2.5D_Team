#include "stdafx.h"
#include "..\Header\RichIDLE.h"

#include "Export_System.h"

#include "SaveLoadMgr.h"
#include "RichPattern1Look.h"

#include "Drop1Look.h"

#include "Rich.h"
#include "RichPhase1.h"

CRichIDLE::CRichIDLE()
{
}

CRichIDLE::~CRichIDLE()
{
}

HRESULT CRichIDLE::Ready_State(CCharacter* pCharacter)
{

	static_cast<CMonster*>(pCharacter)->Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_MonAnimationData(L"RICHSTART"));

	return S_OK;
}

CCharacterState* CRichIDLE::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{

	Add_Count(fTimeDelta);

	/*if (Engine::Key_Down(DIK_H)) {
		return CRichPattern1Look::Create(pCharacter);
	}

	if (Engine::Key_Down(DIK_K)) {
		return CDrop1Look::Create(pCharacter);
	}*/
	/*if (static_cast<CRich*>(pCharacter)->Is_Animation_Frame_End()) {
		return CRichPhase1::Create(pCharacter);
	}*/
	if (m_fCount > 5.f) {
		return CRichPhase1::Create(pCharacter);
	}

	return nullptr;
}

CRichIDLE* CRichIDLE::Create(CCharacter* pCharacter)
{
	CRichIDLE* pInstance = new CRichIDLE();

	if (FAILED(pInstance->Ready_State(pCharacter))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichIDLE::Free(CCharacter* pCharacter)
{
}
