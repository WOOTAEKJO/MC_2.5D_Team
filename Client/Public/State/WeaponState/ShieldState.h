#pragma once
#include "WeaponState.h"
class CShieldState :
    public CWeaponState
{
private:
    explicit CShieldState();
    virtual ~CShieldState();

public:
    virtual HRESULT Ready_State(CCharacter* pcharacter) override;
    virtual CWeaponState* Update_State(CCharacter* pcharacter, const float& fTimeDelta) override;

public:
    static  CShieldState* Create(CCharacter* pcharacter);

private:
    virtual void Free() override;
};

