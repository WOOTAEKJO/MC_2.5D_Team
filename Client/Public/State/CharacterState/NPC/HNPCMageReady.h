#pragma once
#include "CharacterState.h"
class CHNPCMageReady :
    public CCharacterState
{
public:
    explicit    CHNPCMageReady();
    virtual     ~CHNPCMageReady();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHNPCMageReady* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

