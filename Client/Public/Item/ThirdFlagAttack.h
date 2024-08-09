#pragma once
#include "Flagpole.h"
class CThirdFlagAttack :
	public CFlagpole
{
private:
	explicit CThirdFlagAttack(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CThirdFlagAttack(const CThirdFlagAttack& rhs);
	virtual ~CThirdFlagAttack();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
public:
	static	CThirdFlagAttack* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};
