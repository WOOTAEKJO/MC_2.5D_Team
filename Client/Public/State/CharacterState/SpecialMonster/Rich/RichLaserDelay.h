#pragma once
#include "CharacterState.h"
class CRichLaserDelay :
    public CCharacterState
{
public:
    explicit    CRichLaserDelay();
    virtual     ~CRichLaserDelay();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CRichLaserDelay* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

