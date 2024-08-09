#include "stdafx.h"
#include "..\Header\CharacterState.h"

CCharacterState::CCharacterState()
{
}

CCharacterState::~CCharacterState()
{
}

HRESULT CCharacterState::Ready_State(CCharacter* pCharacter)
{
	return S_OK;
}

CCharacterState* CCharacterState::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	return nullptr;
}

void CCharacterState::Free(CCharacter* pCharacter)
{
}
