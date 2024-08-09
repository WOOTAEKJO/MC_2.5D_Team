#pragma once
#include "CharacterState.h"
class CShooterPowerAttack :
    public CCharacterState
{
public:
    explicit    CShooterPowerAttack();
    virtual     ~CShooterPowerAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CShooterPowerAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

