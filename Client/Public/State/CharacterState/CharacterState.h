#pragma once
#include "State.h"
#include "Human.h"
#include "Monster.h"

class CCharacterState :
    public CState
{

public:
    explicit    CCharacterState();
    virtual     ~CCharacterState();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) PURE;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) PURE;

protected:
    void    Add_Count(const float& fTimeDelta) { m_fCount += fTimeDelta; };
    _float  Get_Count() { return m_fCount; };

public:
    virtual void Free(CCharacter* pCharacter);


protected:
    _float     m_fCount = 0.f;
};

