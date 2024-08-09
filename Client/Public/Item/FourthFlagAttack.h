#pragma once
#include "Flagpole.h"
class CFourthFlagAttack :
	public CFlagpole
{
private:
	explicit CFourthFlagAttack(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFourthFlagAttack(const CFourthFlagAttack& rhs);
	virtual ~CFourthFlagAttack();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
public:
	static	CFourthFlagAttack* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};
