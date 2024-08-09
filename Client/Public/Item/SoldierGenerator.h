#pragma once
#include "CubeItem.h"

BEGIN(Engine)

END

class CSoldierGenerator :
    public CCubeItem
{
private:
	explicit CSoldierGenerator(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSoldierGenerator(const CSoldierGenerator& rhs);
	virtual ~CSoldierGenerator();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component();
public:
	static	CSoldierGenerator* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	void	Add_Count(const _float& fTimeDelta) { m_fTime += fTimeDelta; }
private:
	_float		m_fTime = 0.f;
private:
	virtual void Free();
};

