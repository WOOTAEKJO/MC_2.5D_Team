#pragma once
#include "CharacterState.h"
class CChargerAttack :
    public CCharacterState
{
public:
    explicit    CChargerAttack();
    virtual     ~CChargerAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CChargerAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

