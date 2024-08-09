#pragma once
#include "CharacterState.h"
class CArchMageMeteor :
    public CCharacterState
{
public:
    explicit    CArchMageMeteor();
    virtual     ~CArchMageMeteor();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CArchMageMeteor* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

