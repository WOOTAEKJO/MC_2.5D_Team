#pragma once
#include "CharacterState.h"
class CRichDead :
    public CCharacterState
{
public:
    explicit    CRichDead();
    virtual     ~CRichDead();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CRichDead* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

