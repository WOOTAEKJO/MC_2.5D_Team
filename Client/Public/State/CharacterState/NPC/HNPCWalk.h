#pragma once
#include "CharacterState.h"
class CHNPCWalk :
    public CCharacterState
{
public:
    explicit    CHNPCWalk();
    virtual     ~CHNPCWalk();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHNPCWalk* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

