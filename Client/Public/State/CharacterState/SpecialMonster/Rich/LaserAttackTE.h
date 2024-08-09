#pragma once
#include "CharacterState.h"
class CLaserAttackTE :
    public CCharacterState
{
public:
    explicit    CLaserAttackTE();
    virtual     ~CLaserAttackTE();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CLaserAttackTE* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

