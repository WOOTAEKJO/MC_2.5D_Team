#pragma once
#include "WeaponState.h"
class CCrossState :
    public CWeaponState
{
private:
    explicit CCrossState();
    virtual ~CCrossState();

public:
    virtual HRESULT Ready_State(CCharacter* pcharacter) override;
    virtual CWeaponState* Update_State(CCharacter* pcharacter, const float& fTimeDelta) override;

public:
    static  CCrossState* Create(CCharacter* pcharacter);

private:
    virtual void Free() override;
};

