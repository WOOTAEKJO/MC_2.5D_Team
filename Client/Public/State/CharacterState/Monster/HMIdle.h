#pragma once
#include "CharacterState.h"
class CHMIdle :
    public CCharacterState
{
public:
    explicit    CHMIdle();
    virtual     ~CHMIdle();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHMIdle* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

