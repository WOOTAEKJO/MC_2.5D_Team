#pragma once
#include "UIImage.h"

class CBowItemImage :
    public CUIImage
{
private:
	explicit CBowItemImage(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBowItemImage(const CBowItemImage& rhs);
	virtual ~CBowItemImage();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();

public:
	static CBowItemImage* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

