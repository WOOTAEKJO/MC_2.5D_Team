#pragma once
#include "CubeItem.h"
class CShield :
    public CCubeItem
{
private:
	explicit CShield(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CShield(const CShield& rhs);
	virtual ~CShield();
public:
	virtual HRESULT Ready_GameObject(CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType = WEAPONTYPE::WEAPON_END);
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component();
public:
	static	CShield* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pObj, PARTS eParts = PARTS_END, WEAPONTYPE eWeaponType = WEAPONTYPE::WEAPON_END);

private:
	virtual void Free();
};

