#pragma once
#include "UIImage.h"
class CBossGauge :
    public CUIImage
{
private:
	explicit CBossGauge(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBossGauge(const CBossGauge& rhs);
	virtual ~CBossGauge();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

public:
	void	Fill_Gauge();
	void	Set_End_Point(const _vec3& vPos) {
		End_Point = vPos;
	}

	void	Set_Start_Point(const _vec3& vPos) {
		Start_Point = vPos;
	}

private:
	HRESULT		Add_Component();

private:
	_vec3		End_Point = { 0.f,0.f,0.f };
	_vec3		Start_Point = { 0.f,0.f,0.f };

public:
	static CBossGauge* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

