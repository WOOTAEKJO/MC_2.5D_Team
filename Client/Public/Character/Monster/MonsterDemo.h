#pragma once
#include "Monster.h"

BEGIN(Engine)


END
class CMonsterDemo :
    public CMonster
{
private:
	explicit CMonsterDemo(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMonsterDemo(const CMonsterDemo& rhs);
	virtual ~CMonsterDemo();

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
	static CMonsterDemo* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free();

private:
	CMonsterAnimation* m_pDemo;
};

