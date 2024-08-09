#pragma once
#include "UIImage.h"
class CIconBoxUI :
    public CUIImage
{
private:
	explicit CIconBoxUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CIconBoxUI(const CIconBoxUI& rhs);
	virtual ~CIconBoxUI();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();

private:


public:
	static CIconBoxUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

