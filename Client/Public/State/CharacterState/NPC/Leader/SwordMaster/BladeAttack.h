#pragma once
#include "CharacterState.h"
class CBladeAttack :
    public CCharacterState
{
public:
    explicit    CBladeAttack();
    virtual     ~CBladeAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CBladeAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

