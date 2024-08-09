#pragma once
#include "CubeItem.h"

BEGIN(Engine)

class CRigidBody;

END

class CCrystal :
    public CCubeItem
{
private:
	explicit CCrystal(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCrystal(const CCrystal& rhs);
	virtual ~CCrystal();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();
public:
	virtual void		OnCollisionEnter(CCollider* _pOther);
public:
	void	Init_Pos(const _vec3& vPos);
	void	Create_UI();
private:
	virtual HRESULT	Add_Component();
public:
	static	CCrystal* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	CRigidBody* m_pRigidBody = nullptr;
	CGameObject* m_pUI = nullptr;
private:
	virtual void Free();
};

