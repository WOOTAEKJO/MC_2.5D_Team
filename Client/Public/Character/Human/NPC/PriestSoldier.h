#pragma once
#include "HNPC.h"
class CPriestSoldier :
    public CHNPC
{
private:
	explicit CPriestSoldier(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPriestSoldier(const CPriestSoldier& rhs);
	virtual ~CPriestSoldier();

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
	static CPriestSoldier* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

