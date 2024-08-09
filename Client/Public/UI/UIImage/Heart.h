#pragma once

#include "UIImage.h"

BEGIN(Engine)

END

class CHeart : public CUIImage
{
private:
	explicit CHeart(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHeart(const CHeart& rhs);
	virtual ~CHeart();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();

public:
	static CHeart* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

