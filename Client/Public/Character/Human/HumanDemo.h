#pragma once
#include "Human.h"

BEGIN(Engine)


END

class CHumanDemo :
    public CHuman
{
private:
	explicit CHumanDemo(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHumanDemo(const CHumanDemo& rhs);
	virtual ~CHumanDemo();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject() override;
	virtual void	Render_GameObject() override;
public:
	virtual HRESULT	Add_State();
	virtual HRESULT	Add_Component() { return S_OK; }
	virtual HRESULT Add_Weapon(WEAPONTYPE eWeaponType) { return S_OK; }
public:
	static CHumanDemo* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free();

private:
	CHumanAnimation* m_pDemo;
	
};

