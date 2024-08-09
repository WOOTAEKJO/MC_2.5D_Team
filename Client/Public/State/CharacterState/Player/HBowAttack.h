#pragma once
#include "CharacterState.h"
class CHBowAttack :
    public CCharacterState
{
public:
    explicit    CHBowAttack();
    virtual     ~CHBowAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHBowAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

