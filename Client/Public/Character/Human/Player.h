#pragma once
#include "Human.h"
#include "TestBullet.h"


BEGIN(Engine)

END

class CPlayer : public CHuman
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer();
	
public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject() override;
	virtual void	Render_GameObject() override;

	virtual  HRESULT		Add_Weapon(WEAPONTYPE eWeaponType);
	virtual	 HRESULT		Add_Component();

	void			Quick_Move();


private:
	void					Key_Input(const _float& fTimeDelta);
	
private:
	_float				m_FrameCount;
	_float				m_fF;
	_float				m_fSpeed = 3.0f;	

private:
	CGameObject*		m_pManagementUI = nullptr;
	CGameObject*		m_pStoreUI = nullptr;
private:
	CGameObject*		m_pTest = nullptr;
public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free();
};
