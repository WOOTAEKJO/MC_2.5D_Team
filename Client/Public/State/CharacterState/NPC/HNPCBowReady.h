#pragma once
#include "CharacterState.h"
class CHNPCBowReady :
    public CCharacterState
{
public:
    explicit    CHNPCBowReady();
    virtual     ~CHNPCBowReady();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHNPCBowReady* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

