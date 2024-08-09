#pragma once
#include "UIImage.h"

class CBuildMap;

class CMagicAttackTowerCreateButton :
    public CUIImage
{
private:
	explicit CMagicAttackTowerCreateButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMagicAttackTowerCreateButton(const CMagicAttackTowerCreateButton& rhs);
	virtual ~CMagicAttackTowerCreateButton();

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
	static CMagicAttackTowerCreateButton* Create(LPDIRECT3DDEVICE9 pGraphicDev,CUI* pUI);

private:
	_bool		m_bPick_Check = false;
	CBuildMap*	m_pBuildMap = nullptr;
	CUI*		m_pConUI = nullptr;
private:
	virtual void Free() override;
};

