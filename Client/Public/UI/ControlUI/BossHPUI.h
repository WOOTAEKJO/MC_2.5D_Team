#pragma once
#include "ControlUI.h"
class CBossHPUI :
    public CControlUI
{
private:
	explicit CBossHPUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBossHPUI(const CBossHPUI& rhs);
	virtual ~CBossHPUI();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void	Is_Rich_Alive();
private:

	virtual	_vec3	Cal_Pos(_int iNum) {

		return _vec3(0.f, 0.f, 0.f);
	}

private:
	HRESULT		Add_Component();
public:
	virtual HRESULT	Create_ItemImage() override;

public:
	static CBossHPUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

