#pragma once
#include "CharacterState.h"
class CChargerWalk :
    public CCharacterState
{
public:
    explicit    CChargerWalk();
    virtual     ~CChargerWalk();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CChargerWalk* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

