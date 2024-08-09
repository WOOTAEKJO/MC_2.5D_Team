#pragma once
#include "CharacterState.h"
class CShooterAttack :
    public CCharacterState
{
public:
    explicit    CShooterAttack();
    virtual     ~CShooterAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CShooterAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

