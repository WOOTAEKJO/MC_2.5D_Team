#pragma once
#include "Flagpole.h"
class CSwordFlagpole :
    public CFlagpole
{
private:
	explicit CSwordFlagpole(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSwordFlagpole(const CSwordFlagpole& rhs);
	virtual ~CSwordFlagpole();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
public:
	static	CSwordFlagpole* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

