#pragma once
#include "UIImage.h"
class CBossStateUI :
    public CUIImage
{
private:
	explicit CBossStateUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBossStateUI(const CBossStateUI& rhs);
	virtual ~CBossStateUI();

public:
	virtual void Render_GameObject() override;
	HRESULT Ready_GameObject(CUI* pUI);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();
	CUI* m_pUI = nullptr;
public:
	static CBossStateUI* Create(LPDIRECT3DDEVICE9 pGraphicDev,CUI* pUI);

private:
	virtual void Free() override;
};

