#pragma once
#include "CharacterState.h"
class CHNPCIDLE :
    public CCharacterState
{
public:
    explicit    CHNPCIDLE();
    virtual     ~CHNPCIDLE();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHNPCIDLE* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

