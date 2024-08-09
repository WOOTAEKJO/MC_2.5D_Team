#pragma once
#include "CharacterState.h"
class CHNPCBowAttack :
    public CCharacterState
{
public:
    explicit    CHNPCBowAttack();
    virtual     ~CHNPCBowAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHNPCBowAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

