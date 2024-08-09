#pragma once
#include "CharacterState.h"
class CSkeletonAttack :
    public CCharacterState
{
public:
    explicit    CSkeletonAttack();
    virtual     ~CSkeletonAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CSkeletonAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

