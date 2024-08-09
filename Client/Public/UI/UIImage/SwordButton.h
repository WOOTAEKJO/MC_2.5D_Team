#pragma once
#include "UIImage.h"
class CSwordButton :
    public CUIImage
{
private:
	explicit CSwordButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSwordButton(const CSwordButton& rhs);
	virtual ~CSwordButton();

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
	CUI*			m_pUI = nullptr;
public:
	static CSwordButton* Create(LPDIRECT3DDEVICE9 pGraphicDev,const _int& iPirce);

private:
	virtual void Free() override;
};

