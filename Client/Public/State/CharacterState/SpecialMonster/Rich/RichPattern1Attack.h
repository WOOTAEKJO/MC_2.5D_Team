#pragma once
#include "CharacterState.h"
class CRichPattern1Attack :
    public CCharacterState
{
public:
    explicit    CRichPattern1Attack();
    virtual     ~CRichPattern1Attack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CRichPattern1Attack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

