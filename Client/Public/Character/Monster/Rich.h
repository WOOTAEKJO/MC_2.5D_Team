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
	_vec3			m_Random_Pos[12];		// 12 ���� Ÿ�� ��ġ�� ��� �ִ� �迭
private:
	_vec3			m_vStartLook;			// ��ü�� ó�� ���� ���͸� ����
	_bool			m_bArrived[6];			// ETC�� �������� �����ߴ����� �Ǵ�. 
	_int			m_iRIndex[6];			// ���� ��ġ �ε���
	_int			m_iETCIndex[6];			// ETC�� ������ ����
	_int			m_iETC_Num = 0;			// ����� ETC ����
private:
	_int			m_CommendersIndex = 0;	// Ÿ���� �� ���ְ��� �ε���
private:
	CGameObject*	m_pSummon[4];			// ��ȯ���� ����
	_bool			m_bSummonCheck = false;	// ��ȯ���� ��ȯ���� �Ǵ�
private:
	_bool           m_bFlasherCheck = false;	// ����⸦ ����� �������� �Ǵ�.
	_bool			m_bGroggyCheck = false;		// �׷α� ���� �Ǵ�
	_bool			m_bLaserCheck = false;		// ������ ��� �Ǵ�.
	_bool			m_bPhaseChangeCheck = false;	// ���̽� ü���� �Ǵ�.
private:
	RICHPHASETYPE	m_ePhaseType = RICHPHASETYPE::PHASE1;	// ���� ����
private:
	CGameObject*	m_pEffect[6];				// ����Ʈ�� �����ϱ� ����
	CGameObject*	m_pLaserEffect[16];				// ������ ����Ʈ ����
	CGameObject*	m_pLaserRangeEffect[4];		// ������ ���� ����Ʈ ����
private:
	CGameObject*	m_pUI[4];						// UI ����
private:
	_int			m_iGaugeCount = 0;			// ������ ����
private:
	_bool			m_bHPCheck = false;			// ������ ���� �� ���Ϸ� �������� Ȱ��ȭ
private:
	_float			m_fTimeCount = 0.f;
public:
	static CRich* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	
private:
	virtual void Free();
};

