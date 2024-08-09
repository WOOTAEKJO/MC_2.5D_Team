#pragma once
#include "CharacterState.h"
class CShooterPowerReady :
    public CCharacterState
{
public:
    explicit    CShooterPowerReady();
    virtual     ~CShooterPowerReady();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CShooterPowerReady* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

