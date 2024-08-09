#pragma once
#include "Flagpole.h"
class CSecondFlagAttack :
	public CFlagpole
{
private:
	explicit CSecondFlagAttack(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSecondFlagAttack(const CSecondFlagAttack& rhs);
	virtual ~CSecondFlagAttack();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
public:
	static	CSecondFlagAttack* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};
