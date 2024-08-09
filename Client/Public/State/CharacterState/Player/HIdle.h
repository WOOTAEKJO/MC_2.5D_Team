#pragma once
#include "CharacterState.h"
class CHIdle :
    public CCharacterState
{
public:
    explicit    CHIdle();
    virtual     ~CHIdle();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHIdle* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

