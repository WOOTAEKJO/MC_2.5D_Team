#pragma once
#include "CharacterState.h"
class CHNPCShieldBlock :
    public CCharacterState
{
public:
    explicit    CHNPCShieldBlock();
    virtual     ~CHNPCShieldBlock();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHNPCShieldBlock* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

