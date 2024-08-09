#pragma once
#include "ControlUI.h"
class CBossNameBox :
    public CControlUI
{
private:
	explicit CBossNameBox(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBossNameBox(const CBossNameBox& rhs);
	virtual ~CBossNameBox();

public:
	virtual void Render_GameObject() override;
	HRESULT Ready_GameObject(CGameObject* pOwner) ;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
private:

	virtual	_vec3	Cal_Pos(_int iNum) {

		return _vec3(0.f, 0.f, 0.f);
	}

private:
	HRESULT		Add_Component();
public:
	virtual HRESULT	Create_ItemImage() override;
	_bool	Is_Change_State();
public:
	static CBossNameBox* Create(LPDIRECT3DDEVICE9 pGraphicDev,CGameObject* pOwner);
private:
	CGameObject*		m_pOwner = nullptr;
private:
	virtual void Free() override;
};

