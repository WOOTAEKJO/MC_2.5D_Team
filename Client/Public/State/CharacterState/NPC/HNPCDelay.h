#pragma once
#include "CharacterState.h"
class CHNPCDelay :
    public CCharacterState
{
public:
    explicit    CHNPCDelay();
    virtual     ~CHNPCDelay();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;
public:
    static  CHNPCDelay* Create(CCharacter* pCharacter, const _float& fDelTime);
public:
    void    Set_DelTime(const _float& fDelTime) { m_fDelTime = fDelTime; }
private:
    _float m_fDelTime = 0.f;
public:
    virtual void Free(CCharacter* pCharacter);
};

