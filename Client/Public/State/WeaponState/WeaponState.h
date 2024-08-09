#pragma once
#include "State.h"
#include "Human.h"

class CWeaponState :
    public CState
{
public:
    explicit    CWeaponState();
    virtual     ~CWeaponState();

public:
    virtual HRESULT Ready_State(CCharacter* pcharacter);
    virtual CWeaponState* Update_State(CCharacter* pcharacter, const float& fTimeDelta);

public:
    virtual void Free() override;
};

