#pragma once
#include "Flagpole.h"
class CFourthFlagpole :
    public CFlagpole
{
private:
	explicit CFourthFlagpole(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFourthFlagpole(const CFourthFlagpole& rhs);
	virtual ~CFourthFlagpole();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
public:
	static	CFourthFlagpole* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

