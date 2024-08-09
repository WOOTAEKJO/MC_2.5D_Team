#pragma once
#include "ControlUI.h"
class CLoadingUI :
    public CControlUI
{
private:
	explicit CLoadingUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLoadingUI(const CLoadingUI& rhs);
	virtual ~CLoadingUI();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
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

public:
	static CLoadingUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

