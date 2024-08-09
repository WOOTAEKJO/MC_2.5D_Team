#pragma once
#include "Human.h"

BEGIN(Engine)

END

class CHMonster :
    public CHuman
{
protected:
	explicit CHMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHMonster(const CHMonster& rhs);
	virtual ~CHMonster();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject() override;
	virtual void	Render_GameObject() override;

	virtual  HRESULT		Add_Weapon(WEAPONTYPE eWeaponType) PURE;
	virtual	 HRESULT		Add_Component() PURE;
public:
	virtual void		OnCollisionEnter(CCollider* _pOther);
	virtual void		OnCollisionStay(CCollider* _pOther);
	virtual void		OnCollisionExit(CCollider* _pOther);

protected:
	virtual void Free();
};

