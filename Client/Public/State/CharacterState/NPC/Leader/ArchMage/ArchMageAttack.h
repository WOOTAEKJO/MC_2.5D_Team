#pragma once
#include "CharacterState.h"
class CArchMageAttack :
    public CCharacterState
{
public:
    explicit    CArchMageAttack();
    virtual     ~CArchMageAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CArchMageAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

