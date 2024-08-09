#pragma once
#include "CubeItem.h"
class CFlagpole :
	public CCubeItem
{
protected:
	explicit CFlagpole(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFlagpole(const CFlagpole& rhs);
	virtual ~CFlagpole();

public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

protected:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);


public:
	_bool	Get_MoveMode() { return m_bMoveMode; };
	void	Set_MoveMode(_bool _bMoveMode) { m_bMoveMode = _bMoveMode; };

protected:
	virtual void Free();

private:
	_bool m_bMoveMode = false;
};