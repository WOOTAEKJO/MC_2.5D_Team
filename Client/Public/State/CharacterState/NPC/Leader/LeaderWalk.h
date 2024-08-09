#pragma once
#include "CharacterState.h"
class CLeaderWalk :
    public CCharacterState
{
public:
    explicit    CLeaderWalk();
    virtual     ~CLeaderWalk();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CLeaderWalk* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

