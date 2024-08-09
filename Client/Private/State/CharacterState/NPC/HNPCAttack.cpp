#include "stdafx.h"
#include "HNPCAttack.h"
#include "HNPCWalk.h"

CCharacterState* CHNPCAttack::Update_State(CCharacter* pCharacter, const float& fTimeDelta)
{
	if (pCharacter->Get_MoveMode()) 
	{
		return CHNPCWalk::Create(pCharacter);
	}
	return nullptr;
}
