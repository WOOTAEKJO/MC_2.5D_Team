#pragma once
#include "CharacterState.h"
class CDrop1Look :
    public CCharacterState
{
public:
    explicit    CDrop1Look();
    virtual     ~CDrop1Look();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CDrop1Look* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

