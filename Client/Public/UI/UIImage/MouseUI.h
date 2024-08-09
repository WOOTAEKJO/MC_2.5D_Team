#pragma once
#include "UIImage.h"
class CMouseUI :
    public CUIImage
{
private:
	explicit CMouseUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMouseUI(const CMouseUI& rhs);
	virtual ~CMouseUI();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void	Mouse_Pos_Cal();

private:
	HRESULT		Add_Component();

private:


public:
	static CMouseUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

