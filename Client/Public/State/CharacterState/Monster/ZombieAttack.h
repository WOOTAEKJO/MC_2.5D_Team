#pragma once
#include "CharacterState.h"

class CZombieAttack :
    public CCharacterState
{
public:
    explicit    CZombieAttack();
    virtual     ~CZombieAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CZombieAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

