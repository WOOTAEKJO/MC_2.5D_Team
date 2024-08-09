#pragma once
#include "ControlUI.h"
class CManagementUI :
	public CControlUI
{
private:
	explicit CManagementUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CManagementUI(const CManagementUI& rhs);
	virtual ~CManagementUI();

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

	void	Set_UI_Type(MANAGEMENTUITYPE eUIType) { m_eUI_Type = eUIType; }
private:
	MANAGEMENTUITYPE	m_eUI_Type = MANAGEMENTUITYPE::MU_END;
public:
	static CManagementUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

