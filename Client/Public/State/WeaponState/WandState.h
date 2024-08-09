#pragma once
#include "WeaponState.h"
class CWandState :
    public CWeaponState
{
private:
    explicit CWandState();
    virtual ~CWandState();

public:
    virtual HRESULT Ready_State(CCharacter* pcharacter) override;
    virtual CWeaponState* Update_State(CCharacter* pcharacter, const float& fTimeDelta) override;

public:
    static  CWandState* Create(CCharacter* pcharacter);

private:
    virtual void Free() override;
};

