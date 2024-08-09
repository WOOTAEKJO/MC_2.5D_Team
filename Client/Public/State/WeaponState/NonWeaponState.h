#pragma once
#include "WeaponState.h"
class CNonWeaponState :
    public CWeaponState
{

private:
    explicit CNonWeaponState();
    virtual ~CNonWeaponState();

public:
    virtual HRESULT Ready_State(CCharacter* pcharacter) override;
    virtual CWeaponState* Update_State(CCharacter* pcharacter, const float& fTimeDelta) override;

public:
    static  CNonWeaponState* Create(CCharacter* pcharacter);

private:
    virtual void Free() override;

};

