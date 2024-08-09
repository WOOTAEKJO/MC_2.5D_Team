#pragma once
#include "CharacterState.h"
class CRichPattern1Look :
    public CCharacterState
{
public:
    explicit    CRichPattern1Look();
    virtual     ~CRichPattern1Look();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CRichPattern1Look* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

