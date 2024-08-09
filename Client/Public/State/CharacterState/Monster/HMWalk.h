#pragma once
#include "CharacterState.h"
class CHMWalk :
    public CCharacterState
{
    explicit    CHMWalk();
    virtual     ~CHMWalk();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHMWalk* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

