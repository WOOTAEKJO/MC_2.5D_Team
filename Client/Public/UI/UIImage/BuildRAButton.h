#pragma once
#include "UIImage.h"
class CBuildRAButton :
    public CUIImage
{
private:
	explicit CBuildRAButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBuildRAButton(const CBuildRAButton& rhs);
	virtual ~CBuildRAButton();

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
	static CBuildRAButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI);

private:
	virtual void Free() override;
};

