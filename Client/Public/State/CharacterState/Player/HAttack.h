#pragma once
#include "CharacterState.h"
class CHAttack :
    public CCharacterState
{
public:
    explicit    CHAttack();
    virtual     ~CHAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

