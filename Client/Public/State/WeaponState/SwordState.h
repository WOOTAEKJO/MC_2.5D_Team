#pragma once
#include "WeaponState.h"
class CSwordState :
    public CWeaponState
{
private:
    explicit CSwordState();
    virtual ~CSwordState();

public:
    virtual HRESULT Ready_State(CCharacter* pcharacter) override;
    virtual CWeaponState* Update_State(CCharacter* pcharacter, const float& fTimeDelta) override;

public:
    static  CSwordState* Create(CCharacter* pcharacter);

private:
    virtual void Free() override;
};

