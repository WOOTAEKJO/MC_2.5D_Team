#pragma once
#include "CharacterState.h"
class CRichPhase1 :
    public CCharacterState
{
public:
    enum SUMMONTYPE {ZOMBIE_SUM = 1,CRYSTAL_SUM,SUM_END};
public:
    explicit    CRichPhase1();
    virtual     ~CRichPhase1();

public:
    virtual HRESULT Ready_State(CCharacter* pCharacter) override;
    virtual CCharacterState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) override;  
public:
    void    Crystal_State(CCharacter* pCharacter, const float& fTimeDelta);
private:
    CCharacterState* m_pState = nullptr;
    SUMMONTYPE      m_eSumType = SUM_END;
public:
    static  CRichPhase1* Create(CCharacter* pCharacter);
public:
    virtual void Free(CCharacter* pCharacter);
};

