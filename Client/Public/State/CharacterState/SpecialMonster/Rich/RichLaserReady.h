#pragma once
#include "CharacterState.h"
class CRichLaserReady :
    public CCharacterState
{
public:
    explicit    CRichLaserReady();
    virtual     ~CRichLaserReady();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CRichLaserReady* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

