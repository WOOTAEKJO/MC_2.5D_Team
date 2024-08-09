#pragma once
#include "UIImage.h"

class CBuildMap;

class CSchoolCreateButton :
    public CUIImage
{
private:
	explicit CSchoolCreateButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSchoolCreateButton(const CSchoolCreateButton& rhs);
	virtual ~CSchoolCreateButton();

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
	static CSchoolCreateButton* Create(LPDIRECT3DDEVICE9 pGraphicDev,CUI* pUI);

private:
	_bool		m_bPick_Check = false;
	CBuildMap*	m_pBuildMap = nullptr;
	CUI*		m_pConUI = nullptr;
private:
	virtual void Free() override;
};

