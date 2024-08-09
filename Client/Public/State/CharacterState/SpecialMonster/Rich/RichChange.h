#pragma once
#include "CharacterState.h"
class CRichChange :
    public CCharacterState
{
public:
    explicit    CRichChange();
    virtual     ~CRichChange();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CRichChange* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

