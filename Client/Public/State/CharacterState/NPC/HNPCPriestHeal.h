#pragma once
#include "CharacterState.h"
class CHNPCPriestHeal :
    public CCharacterState
{
public:
    explicit    CHNPCPriestHeal();
    virtual     ~CHNPCPriestHeal();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHNPCPriestHeal* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

