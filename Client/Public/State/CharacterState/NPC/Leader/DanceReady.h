#pragma once
#include "CharacterState.h"
class CDanceReady :
    public CCharacterState
{
public:
    explicit    CDanceReady();
    virtual     ~CDanceReady();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CDanceReady* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

