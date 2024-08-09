#pragma once
#include "Monster.h"
class CRich :
    public CMonster
{
public:
	enum RICHPHASETYPE {GROGGY,PHASE1,PHASE2,PHASE_END};
	enum RICHLASERTYPE {CROSS,EX,LASER_END};
private:
	explicit CRich(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRich(const CRich& rhs);
	virtual ~CRich();
public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject() override;
	virtual void	Render_GameObject() override;

	virtual  HRESULT		Add_Weapon(WEAPONTYPE eWeaponType) override;
	virtual	 HRESULT		Add_Component() override;

	virtual void		OnCollisionEnter(CCollider* _pOther);
	virtual void		OnCollisionStay(CCollider* _pOther);
	virtual void		OnCollisionExit(CCollider* _pOther);

public:
	void			Reset_Random_Pos();
	void			ETC_ROT();
	void			ETC_LookAT();
	void			ETC_Move(const _float& fTimeDelta, const _float& _fSpeed);
	_bool			ETC_Is_Arrived(const _float& fTimeDelta);
	void			HEAD_Target_Turn();
public:
	void			ETC_Commenders_TargetSet(const _int& iNum);
public:
	void			ETC_Dir_Turn(CTransform* vETC, _vec3* vTargetPos);
public:
	void			Summoner(const _int& iNum);
	void			Delete_Summoner();
	_bool			Is_Summon_Dead();
public:
	void			Set_SummonCheck(_bool bCheck) { m_bSummonCheck = bCheck; }
	_bool			Get_SummonCheck() { return m_bSummonCheck; }
public:
	void			Set_FlasherCheck(_bool bCheck) { m_bFlasherCheck = bCheck; }
	_bool			Get_FlasherCheck() { return m_bFlasherCheck; }
	void			Set_GroggyCheck(_bool bCheck) { m_bGroggyCheck = bCheck; }
	_bool			Get_GroggyCheck() { return m_bGroggyCheck; }
	void			Set_LaserCheck(_bool bCheck) {
		m_bLaserCheck = bCheck;
		if (bCheck == false) {
			m_iGaugeCount = 0;
		}
	}
	_bool			Get_LaserCheck() { return m_bLaserCheck; }
public:
	void			Set_PhaseType(RICHPHASETYPE eType) { m_ePhaseType = eType; }
	RICHPHASETYPE	Get_PhaseType() { return m_ePhaseType; }
public:
	void			Create_ETC_Attack_Range();
	void			Delete_ETC_Attack_Range();
	void			ETC_ATTCOL();
public:
	_int&			Get_GaugeCount() { return m_iGaugeCount; }
public:
	void			Create_Boss_UI();
public:
	void			Laser_Create(RICHLASERTYPE eType);
	void			LaserRange_Create(RICHLASERTYPE eType);
	void			Delete_LaserRange();
	_bool			Is_Laser_Animation_End();
public:
	void			Is_Dead();
	void			Is_Phase2();
public:
	void			Change_Tex() { m_iTex_Num = 1; }
	void			Set_PhaseChangeCheck(_bool bCheck) { m_bPhaseChangeCheck = bCheck; }
	_bool			Get_PhaseChangeCheck() { return m_bPhaseChangeCheck; }
public:
	void			Create_Drop_Effect();
private:
	_vec3			m_Random_Pos[12];		// 12 방향 타겟 위치를 담고 있는 배열
private:
	_vec3			m_vStartLook;			// 본체의 처음 방향 벡터를 저장
	_bool			m_bArrived[6];			// ETC가 목적지에 도착했는지를 판단. 
	_int			m_iRIndex[6];			// 랜덤 위치 인덱스
	_int			m_iETCIndex[6];			// ETC의 순서를 결정
	_int			m_iETC_Num = 0;			// 사용할 ETC 갯수
private:
	_int			m_CommendersIndex = 0;	// 타겟이 될 지휘관의 인덱스
private:
	CGameObject*	m_pSummon[4];			// 소환수를 저장
	_bool			m_bSummonCheck = false;	// 소환수를 소환할지 판단
private:
	_bool           m_bFlasherCheck = false;	// 점멸기를 사용할 것인지를 판단.
	_bool			m_bGroggyCheck = false;		// 그로기 상태 판단
	_bool			m_bLaserCheck = false;		// 레이저 사용 판단.
	_bool			m_bPhaseChangeCheck = false;	// 페이스 체인지 판단.
private:
	RICHPHASETYPE	m_ePhaseType = RICHPHASETYPE::PHASE1;	// 보스 상태
private:
	CGameObject*	m_pEffect[6];				// 이펙트를 관리하기 위해
	CGameObject*	m_pLaserEffect[16];				// 레이저 이펙트 관리
	CGameObject*	m_pLaserRangeEffect[4];		// 레이저 범위 이펙트 관리
private:
	CGameObject*	m_pUI[4];						// UI 관리
private:
	_int			m_iGaugeCount = 0;			// 게이지 관리
private:
	_bool			m_bHPCheck = false;			// 보스가 일정 피 이하로 떨어지면 활성화
private:
	_float			m_fTimeCount = 0.f;
public:
	static CRich* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	
private:
	virtual void Free();
};

