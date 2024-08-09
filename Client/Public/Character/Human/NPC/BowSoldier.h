#pragma once
#include "HNPC.h"
class CBowSoldier :
    public CHNPC
{
private:
	explicit CBowSoldier(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBowSoldier(const CBowSoldier& rhs);
	virtual ~CBowSoldier();

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
	static CBowSoldier* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

