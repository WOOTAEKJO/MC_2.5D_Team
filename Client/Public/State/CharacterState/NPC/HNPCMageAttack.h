#pragma once
#include "CharacterState.h"
class CHNPCMageAttack :
    public CCharacterState
{
public:
    explicit    CHNPCMageAttack();
    virtual     ~CHNPCMageAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHNPCMageAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

