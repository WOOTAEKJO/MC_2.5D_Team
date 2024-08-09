#pragma once
#include "UIImage.h"
class CSwordMasterButton :
    public CUIImage
{
private:
	explicit CSwordMasterButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSwordMasterButton(const CSwordMasterButton& rhs);
	virtual ~CSwordMasterButton();

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
	static CSwordMasterButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _int& iPirce);

private:
	virtual void Free() override;
};

