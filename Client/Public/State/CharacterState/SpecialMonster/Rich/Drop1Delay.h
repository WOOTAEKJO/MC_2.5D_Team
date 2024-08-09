#pragma once
#include "CharacterState.h"
class CDrop1Delay :
    public CCharacterState
{
public:
    explicit    CDrop1Delay();
    virtual     ~CDrop1Delay();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CDrop1Delay* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

