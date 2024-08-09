#pragma once
#include "CharacterState.h"
class CHWalk :
    public CCharacterState
{
public:
    explicit    CHWalk();
    virtual     ~CHWalk();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHWalk* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

