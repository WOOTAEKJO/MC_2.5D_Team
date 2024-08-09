#pragma once
#include "UIImage.h"
class CLAButton :
    public CUIImage
{
private:
	explicit CLAButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLAButton(const CLAButton& rhs);
	virtual ~CLAButton();

public:
	virtual void Render_GameObject() override;
	HRESULT Ready_GameObject(CUI* pUI);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();
private:
	CUI* m_pUI = nullptr;
public:
	static CLAButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI);

private:
	virtual void Free() override;
};

