#pragma once
#include "ControlUI.h"

class CPlayerStateUI : public CControlUI
{
private:
	explicit CPlayerStateUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayerStateUI(const CPlayerStateUI& rhs);
	virtual ~CPlayerStateUI();

public:
	virtual HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject();
private:
	virtual	_vec3	Cal_Pos(_int iNum) {

		return _vec3(-190.f + (17.f * iNum), -220.f, 1.f);
	}

	void	Player_HP_UI_Update();

private:
	HRESULT		Add_Component();
public:
	virtual HRESULT	Create_ItemImage() override;
private:
	CGameObject* m_pPlayerInfo = nullptr;
private:
	_bool		m_bHP_Check = false;
	_int		m_iMaxHP = 0;
public:
	static CPlayerStateUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free() override;
};

