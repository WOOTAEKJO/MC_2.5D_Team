#pragma once
#include "Flagpole.h"
class CSecondFlagpole :
    public CFlagpole
{
private:
	explicit CSecondFlagpole(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSecondFlagpole(const CSecondFlagpole& rhs);
	virtual ~CSecondFlagpole();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
public:
	static	CSecondFlagpole* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

