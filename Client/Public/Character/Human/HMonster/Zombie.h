#pragma once
#include "HMonster.h"

BEGIN(Engine)

END

class CZombie :
    public CHMonster
{
private:
	explicit CZombie(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CZombie(const CZombie& rhs);
	virtual ~CZombie();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject() override;
	virtual void	Render_GameObject() override;

	virtual  HRESULT		Add_Weapon(WEAPONTYPE eWeaponType) override;
	virtual	 HRESULT		Add_Component() override;

	virtual void		OnCollisionEnter(CCollider* _pOther) { CHMonster::OnCollisionEnter(_pOther); };
	virtual void		OnCollisionStay(CCollider* _pOther) { CHMonster::OnCollisionStay(_pOther); };
	virtual void		OnCollisionExit(CCollider* _pOther) { CHMonster::OnCollisionExit(_pOther); };

public:
	static CZombie* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

