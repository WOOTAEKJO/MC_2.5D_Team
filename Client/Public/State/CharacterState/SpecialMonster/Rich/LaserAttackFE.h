#pragma once
#include "CharacterState.h"
class CLaserAttackFE :
    public CCharacterState
{
public:
    explicit    CLaserAttackFE();
    virtual     ~CLaserAttackFE();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CLaserAttackFE* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

