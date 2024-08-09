#pragma once
#include "UIImage.h"
class CShooterButton :
    public CUIImage
{
private:
	explicit CShooterButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CShooterButton(const CShooterButton& rhs);
	virtual ~CShooterButton();

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
	static CShooterButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _int& iPirce);

private:
	virtual void Free() override;
};

