#pragma once
#include "Monster.h"
class CCharger :
    public CMonster
{
private:
	explicit CCharger(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCharger(const CCharger& rhs);
	virtual ~CCharger();

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
	static CCharger* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

