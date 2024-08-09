#pragma once
#include "CharacterState.h"
class CChargerIDLE :
    public CCharacterState
{
public:
    explicit    CChargerIDLE();
    virtual     ~CChargerIDLE();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CChargerIDLE* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

