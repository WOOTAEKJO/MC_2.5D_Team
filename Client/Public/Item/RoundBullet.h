#pragma once
#include "CubeItem.h"
class CRoundBullet :
    public CCubeItem
{
	explicit CRoundBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRoundBullet(const CRoundBullet& rhs);
	virtual ~CRoundBullet();
public:
	virtual HRESULT Ready_GameObject(CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType = WEAPONTYPE::WEAPON_END);
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();
public:
	virtual void		OnCollisionEnter(CCollider* _pOther);
	virtual void		OnCollisionStay(CCollider* _pOther);
	virtual void		OnCollisionExit(CCollider* _pOther);
public:
	_float			Calc_Distance(_vec3 targetPos);
	void			Active_Bullet();
private:
	virtual HRESULT	Add_Component();
public:
	static	CRoundBullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pObj, PARTS eParts = PARTS_END, WEAPONTYPE eWeaponType = WEAPONTYPE::WEAPON_END);

private:
	_float	m_fCount = 0.f;

	_ushort	m_iCount = 0;
	_ushort m_iTargetSettingCount = 0;
	_float	m_fDelay = 0;

	_float	m_fSpeed = 50.f;

	_vec3	m_vTargetPos;
	_bool	m_bFlag = false;

private:
	virtual void Free();

};

