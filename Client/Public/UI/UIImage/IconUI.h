#pragma once
#include "UIImage.h"
class CIconUI :
    public CUIImage
{
private:
	explicit CIconUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CIconUI(const CIconUI& rhs);
	virtual ~CIconUI();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();

private:


public:
	static CIconUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

