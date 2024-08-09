#pragma once
#include "Flagpole.h"
class CThirdFlagpole :
    public CFlagpole
{
private:
	explicit CThirdFlagpole(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CThirdFlagpole(const CThirdFlagpole& rhs);
	virtual ~CThirdFlagpole();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
public:
	static	CThirdFlagpole* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

