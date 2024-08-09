#pragma once
#include "CharacterState.h"
class CRichPattern1Delay :
    public CCharacterState
{
public:
    explicit    CRichPattern1Delay();
    virtual     ~CRichPattern1Delay();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CRichPattern1Delay* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

