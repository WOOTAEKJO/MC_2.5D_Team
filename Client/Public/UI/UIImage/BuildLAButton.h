#pragma once
#include "UIImage.h"
class CBuildLAButton :
    public CUIImage
{
private:
	explicit CBuildLAButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBuildLAButton(const CBuildLAButton& rhs);
	virtual ~CBuildLAButton();

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
	static CBuildLAButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI);

private:
	virtual void Free() override;
};

