#pragma once
#include "CharacterState.h"
class CRichIDLE :
    public CCharacterState
{
public:
    explicit    CRichIDLE();
    virtual     ~CRichIDLE();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CRichIDLE* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

