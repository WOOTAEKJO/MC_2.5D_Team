#pragma once
#include "ControlUI.h"
class CProgressUI :
    public CControlUI
{
private:
	explicit CProgressUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CProgressUI(const CProgressUI& rhs);
	virtual ~CProgressUI();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void	Cur_Progress();
private:

	virtual	_vec3	Cal_Pos(_int iNum) {

		return _vec3(0.f, 0.f, 0.f);
	}

private:
	HRESULT		Add_Component();
public:
	virtual HRESULT	Create_ItemImage() override;

public:
	static CProgressUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	CUI* m_pBox[4];
	CUI* m_pIcon[4];
	CUI* m_pBar[3];

private:
	virtual void Free() override;
};

