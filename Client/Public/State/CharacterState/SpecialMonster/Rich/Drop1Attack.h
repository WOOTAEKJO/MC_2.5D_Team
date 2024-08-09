#pragma once
#include "CharacterState.h"
class CDrop1Attack :
    public CCharacterState
{
public:
    explicit    CDrop1Attack();
    virtual     ~CDrop1Attack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CDrop1Attack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

