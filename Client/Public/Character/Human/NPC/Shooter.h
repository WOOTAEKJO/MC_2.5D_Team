#pragma once
#include "HNPC.h"
class CShooter :
    public CHNPC
{
private:
	explicit CShooter(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CShooter(const CShooter& rhs);
	virtual ~CShooter();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject() override;
	virtual void	Render_GameObject() override;

	virtual  HRESULT		Add_Weapon(WEAPONTYPE eWeaponType);
	virtual	 HRESULT		Add_Component();
public:
	virtual void		OnCollisionEnter(CCollider* _pOther) { CHNPC::OnCollisionEnter(_pOther); };
	virtual void		OnCollisionStay(CCollider* _pOther) { CHNPC::OnCollisionStay(_pOther); };
	virtual void		OnCollisionExit(CCollider* _pOther) { CHNPC::OnCollisionExit(_pOther); };
public:
	void	One_Attack_Count() { m_iAttackCount += 1; }
	void	Reset_Attack_Count() { m_iAttackCount = 0; }
	_int&	Get_Attack_Count() { return m_iAttackCount; }
public:
	void	Create_Arrow();
	void Create_Arrow_Multi();
public:
	static CShooter* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	_int	m_iAttackCount = 0;

private:
	virtual void Free();
};

