#pragma once
#include "Human.h"

BEGIN(Engine)

END

class CHNPC :
    public CHuman
{
protected:
	explicit CHNPC(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHNPC(const CHNPC& rhs);
	virtual ~CHNPC();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject() override;
	virtual void	Render_GameObject() override;

	virtual  HRESULT		Add_Weapon(WEAPONTYPE eWeaponType) PURE;
	virtual	 HRESULT		Add_Component() PURE;
public:
	virtual void		OnCollisionEnter(CCollider* _pOther);
	virtual void		OnCollisionStay(CCollider* _pOther);
	virtual void		OnCollisionExit(CCollider* _pOther);
public:
	void			Set_UI_Object(CGameObject* pObj) { m_pUI = pObj; }
protected:
	CGameObject*		m_pUI = nullptr;

protected:
	virtual void Free();
};

