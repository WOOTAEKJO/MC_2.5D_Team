#pragma once
#include "CharacterState.h"
class CHNPCAttack :
    public CCharacterState
{
public:
    explicit    CHNPCAttack() {};
    virtual     ~CHNPCAttack() {};

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) { return S_OK; };
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;

};

