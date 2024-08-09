#pragma once
#include "UIImage.h"

class CBuildMap;

class CTrap3CreateButton :
    public CUIImage
{
private:
	explicit CTrap3CreateButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTrap3CreateButton(const CTrap3CreateButton& rhs);
	virtual ~CTrap3CreateButton();

public:
	virtual void Render_GameObject() override;
	HRESULT Ready_GameObject(CUI* pUI);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

public:
	_bool		Get_PichCheck() { return m_bPick_Check; }
private:
	HRESULT		Add_Component();

public:
	static CTrap3CreateButton* Create(LPDIRECT3DDEVICE9 pGraphicDev,CUI* pUI);

private:
	_bool		m_bPick_Check = false;
	CBuildMap*	m_pBuildMap = nullptr;
	CUI*		m_pConUI = nullptr;
private:
	virtual void Free() override;
};

