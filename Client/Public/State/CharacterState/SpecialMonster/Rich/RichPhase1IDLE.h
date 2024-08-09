#pragma once
#include "CharacterState.h"
class CRichPhase1IDLE :
    public CCharacterState
{
public:
    explicit    CRichPhase1IDLE();
    virtual     ~CRichPhase1IDLE();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CRichPhase1IDLE* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

