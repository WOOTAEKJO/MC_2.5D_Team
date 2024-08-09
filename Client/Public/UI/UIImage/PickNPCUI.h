#pragma once
#include "UIImage.h"
class CPickNPCUI :
    public CUIImage
{
private:
	explicit CPickNPCUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPickNPCUI(const CPickNPCUI& rhs);
	virtual ~CPickNPCUI();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void	Cal_Pos();
private:
	HRESULT		Add_Component();

public:
	static CPickNPCUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

