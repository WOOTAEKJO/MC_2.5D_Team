#pragma once
#include "CharacterState.h"
class CLaserAttackSC :
    public CCharacterState
{
public:
    explicit    CLaserAttackSC();
    virtual     ~CLaserAttackSC();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CLaserAttackSC* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

