#pragma once
#include "UIImage.h"
class CArchMageButton :
    public CUIImage
{
private:
	explicit CArchMageButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CArchMageButton(const CArchMageButton& rhs);
	virtual ~CArchMageButton();

public:
	virtual void Render_GameObject() override;
	HRESULT Ready_GameObject(const _int& iPirce);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();
private:
	_int		m_iPrice = 0;

public:
	static CArchMageButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _int& iPirce);

private:
	virtual void Free() override;
};

