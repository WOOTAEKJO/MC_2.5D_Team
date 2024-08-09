#pragma once
#include "WeaponState.h"
class CBowState :
    public CWeaponState
{
private:
    explicit CBowState();
    virtual ~CBowState();

public:
    virtual HRESULT Ready_State(CCharacter* pcharacter) override;
    virtual CWeaponState* Update_State(CCharacter* pcharacter, const float& fTimeDelta) override;

public:
    static  CBowState* Create(CCharacter* pcharacter);

private:
    virtual void Free() override;
};

