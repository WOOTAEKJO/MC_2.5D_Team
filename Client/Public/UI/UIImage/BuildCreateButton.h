#pragma once
#include "UIImage.h"
class CBuildCreateButton :
    public CUIImage
{
private:
	explicit CBuildCreateButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBuildCreateButton(const CBuildCreateButton& rhs);
	virtual ~CBuildCreateButton();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();

public:
	static CBuildCreateButton* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

