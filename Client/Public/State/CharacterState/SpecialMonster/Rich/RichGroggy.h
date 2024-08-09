#pragma once
#include "CharacterState.h"
class CRichGroggy :
    public CCharacterState
{
public:
    explicit    CRichGroggy();
    virtual     ~CRichGroggy();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CRichGroggy* Create(CCharacter* pCharacter);
private:
    _int        m_iCurHP = 0;
public:
    virtual void Free(CCharacter* pCharacter);
};

