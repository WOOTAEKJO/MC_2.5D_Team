#pragma once
#include "Flagpole.h"
class CFirstFlagAttack :
    public CFlagpole
{
private:
	explicit CFirstFlagAttack(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFirstFlagAttack(const CFirstFlagAttack& rhs);
	virtual ~CFirstFlagAttack();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
public:
	static	CFirstFlagAttack* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

