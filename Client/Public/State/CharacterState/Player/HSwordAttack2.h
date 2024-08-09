#pragma once
#include "CharacterState.h"
class CHSwordAttack2 :
    public CCharacterState
{
public:
    explicit    CHSwordAttack2();
    virtual     ~CHSwordAttack2();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHSwordAttack2* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

