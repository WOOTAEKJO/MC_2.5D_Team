#pragma once
#include "UIImage.h"
class CEmerald :
    public CUIImage
{
private:
	explicit CEmerald(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CEmerald(const CEmerald& rhs);
	virtual ~CEmerald();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();

private:


public:
	static CEmerald* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

