#pragma once
#include "UIImage.h"
class CRAButton :
    public CUIImage
{
private:
	explicit CRAButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRAButton(const CRAButton& rhs);
	virtual ~CRAButton();

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
	static CRAButton* Create(LPDIRECT3DDEVICE9 pGraphicDev,CUI* pUI);

private:
	virtual void Free() override;
};

