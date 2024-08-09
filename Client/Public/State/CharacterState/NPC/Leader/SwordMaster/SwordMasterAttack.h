#pragma once
#include "CharacterState.h"
class CSwordMasterAttack :
    public CCharacterState
{
public:
    explicit    CSwordMasterAttack();
    virtual     ~CSwordMasterAttack();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CSwordMasterAttack* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

