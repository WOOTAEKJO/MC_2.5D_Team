#pragma once
#include "CharacterState.h"
class CChargerRush :
    public CCharacterState
{
public:
    explicit    CChargerRush();
    virtual     ~CChargerRush();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CChargerRush* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

