#pragma once
#include "CharacterState.h"

class CSwordRushAttack :
    public CCharacterState
{
public:
    explicit    CSwordRushAttack();
    virtual     ~CSwordRushAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CSwordRushAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

