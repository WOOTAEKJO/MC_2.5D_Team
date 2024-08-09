#pragma once
#include "CharacterState.h"
class CSkeletonReady :
    public CCharacterState
{
public:
    explicit    CSkeletonReady();
    virtual     ~CSkeletonReady();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CSkeletonReady* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

