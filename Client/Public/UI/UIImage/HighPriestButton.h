#pragma once
#include "UIImage.h"
class CHighPriestButton :
    public CUIImage
{
private:
	explicit CHighPriestButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHighPriestButton(const CHighPriestButton& rhs);
	virtual ~CHighPriestButton();

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
	static CHighPriestButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _int& iPirce);

private:
	virtual void Free() override;
};

