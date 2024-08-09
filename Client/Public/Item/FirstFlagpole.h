#pragma once
#include "Flagpole.h"
class CFirstFlagpole :
    public CFlagpole
{
private:
	explicit CFirstFlagpole(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFirstFlagpole(const CFirstFlagpole& rhs);
	virtual ~CFirstFlagpole();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
public:
	static	CFirstFlagpole* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

