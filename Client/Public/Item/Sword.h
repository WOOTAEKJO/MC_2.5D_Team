#pragma once
#include "CubeItem.h"

BEGIN(Engine)


END

class CSword :
	public CCubeItem
{
private:
	explicit CSword(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSword(const CSword& rhs);
	virtual ~CSword();
public:
	virtual HRESULT Ready_GameObject(CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType = WEAPONTYPE::WEAPON_END);
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
public:
	static	CSword* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pObj,PARTS eParts = PARTS_END, WEAPONTYPE eWeaponType = WEAPONTYPE::WEAPON_END);

private:
	virtual void Free();
};

