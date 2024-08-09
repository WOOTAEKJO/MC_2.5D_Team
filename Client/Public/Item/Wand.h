#pragma once
#include "CubeItem.h"
class CWand :
    public CCubeItem
{
private:
	explicit CWand(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CWand(const CWand& rhs);
	virtual ~CWand();
public:
	virtual HRESULT Ready_GameObject(CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType = WEAPONTYPE::WEAPON_END);
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component();
public:
	static	CWand* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pObj, PARTS eParts = PARTS_END, WEAPONTYPE eWeaponType = WEAPONTYPE::WEAPON_END);

private:
	virtual void Free();
};

