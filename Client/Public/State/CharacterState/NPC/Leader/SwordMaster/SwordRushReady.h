#pragma once
#include "CharacterState.h"
class CSwordRushReady :
    public CCharacterState
{
public:
    explicit    CSwordRushReady();
    virtual     ~CSwordRushReady();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CSwordRushReady* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

