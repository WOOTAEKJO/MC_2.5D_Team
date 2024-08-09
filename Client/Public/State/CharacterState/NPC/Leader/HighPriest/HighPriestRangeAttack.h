#pragma once
#include "CharacterState.h"
class CHighPriestRangeAttack :
    public CCharacterState
{
public:
    explicit    CHighPriestRangeAttack();
    virtual     ~CHighPriestRangeAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
private:
    _float  m_fHealCount = 0.f;
public:
    static  CHighPriestRangeAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

