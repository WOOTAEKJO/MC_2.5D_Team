#pragma once
#include "CharacterState.h"
class CLaserAttackTC :
    public CCharacterState
{
public:
    explicit    CLaserAttackTC();
    virtual     ~CLaserAttackTC();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CLaserAttackTC* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

