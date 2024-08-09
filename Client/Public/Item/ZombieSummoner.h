#pragma once
#include "CubeItem.h"
class CZombieSummoner :
    public CCubeItem
{
private:
	explicit CZombieSummoner(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CZombieSummoner(const CZombieSummoner& rhs);
	virtual ~CZombieSummoner();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();
public:
	void	Zombie_Summons();
	void	Init_Pos(const _vec3& vPos);
private:
	virtual HRESULT	Add_Component();
public:
	static	CZombieSummoner* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	void	Add_Count(const _float& fTimeDelta) { m_fTime += fTimeDelta; }
private:
	_float		m_fTime = 0.f;							// ½Ã°£
	_int		m_iOrder = 0;
private:
	virtual void Free();
};

