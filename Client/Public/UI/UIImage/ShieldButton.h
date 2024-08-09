#pragma once
#include "UIImage.h"
class CShieldButton :
    public CUIImage
{
private:
	explicit CShieldButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CShieldButton(const CShieldButton& rhs);
	virtual ~CShieldButton();

public:
	virtual void Render_GameObject() override;
	HRESULT Ready_GameObject(const _int& iPirce);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void		Set_OwnerUI(CUI* pUI) { m_pUI = pUI; }
private:
	HRESULT		Add_Component();
private:
	_int		m_iPrice = 0;
	CUI* m_pUI = nullptr;
public:
	static CShieldButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _int& iPirce);

private:
	virtual void Free() override;
};

