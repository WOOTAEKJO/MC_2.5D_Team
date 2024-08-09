#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CEventMgr :
    public CBase
{
    DECLARE_SINGLETON(CEventMgr)

private:
    explicit    CEventMgr();
    virtual     ~CEventMgr();

public:
    HRESULT     Ready_EventMgr();
    void        Update_EventMgr(const _float& fTimeDelta);
    void        Render_EventMgr();

public:
    void        Add_Count(const _float& fTimeDelta) { m_fTime += fTimeDelta; }
    void        Ready_Next_Round();
    void        Active_Wave();
    void        Time_Countdown(const _float& fTimeDelta);
    _int        Get_RoundCount() { return m_iRoundCount; };
public:
    //vector<GENERATORINFO*>* Get_MonsterInfo() { return &m_vecMonsterInfo; }
private:
    _float      m_fTime=0.f;            // �ð�
    _int        m_iRoundCount = 0;      // ���� ��
    _bool       m_bNextRoundCheck = false; // ���� ����

    _float      m_fSoundDelay = 0;
    _float      m_bIsWaveDelay = 15.f;

    
    //vector<GENERATORINFO*>  m_vecMonsterInfo;
private:
    virtual void    Free();
};

END

