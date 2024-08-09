#pragma once
#include "UIImage.h"
class CSwordItemImage :
    public CUIImage
{
private:
	explicit CSwordItemImage(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSwordItemImage(const CSwordItemImage& rhs);
	virtual ~CSwordItemImage();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();

public:
	static CSwordItemImage* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

