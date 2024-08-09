#pragma once
#include "CharacterState.h"
class CShooterDelay :
    public CCharacterState
{
public:
    explicit    CShooterDelay();
    virtual     ~CShooterDelay();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CShooterDelay* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

