#pragma once
#include "CharacterState.h"
#include "HNPCAttack.h"
class CHNPCSwordAttack :
    public CHNPCAttack
{
public:
    explicit    CHNPCSwordAttack();
    virtual     ~CHNPCSwordAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHNPCSwordAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

