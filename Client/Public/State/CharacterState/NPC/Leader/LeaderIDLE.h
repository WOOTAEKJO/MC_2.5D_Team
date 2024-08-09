#pragma once
#include "CharacterState.h"
class CLeaderIDLE :
    public CCharacterState
{
public:
    explicit    CLeaderIDLE();
    virtual     ~CLeaderIDLE();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CLeaderIDLE* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

