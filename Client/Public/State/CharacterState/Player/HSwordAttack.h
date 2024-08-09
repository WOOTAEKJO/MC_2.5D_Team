#pragma once
#include "CharacterState.h"
class CHSwordAttack :
    public CCharacterState
{
public:
    explicit    CHSwordAttack();
    virtual     ~CHSwordAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHSwordAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

