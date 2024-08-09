#pragma once
#include "UIImage.h"
class CBossHP :
    public CUIImage
{
private:
	explicit CBossHP(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBossHP(const CBossHP& rhs);
	virtual ~CBossHP();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void	Cut_HP();

private:
	HRESULT		Add_Component();

private:
	_vec3		Start_Point = {0.f,0.f,0.f};

public:
	static CBossHP* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

