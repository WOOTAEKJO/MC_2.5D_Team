#pragma once
#include "CharacterState.h"
class CDanceStart :
    public CCharacterState
{
public:
    explicit    CDanceStart();
    virtual     ~CDanceStart();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CDanceStart* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

