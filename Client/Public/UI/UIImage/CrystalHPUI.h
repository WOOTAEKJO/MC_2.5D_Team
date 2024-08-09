#pragma once
#include "UIImage.h"

BEGIN(Engine)

class CRcTexLeft;

END

class CCrystalHPUI :
    public CUIImage
{
private:
	explicit CCrystalHPUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCrystalHPUI(const CCrystalHPUI& rhs);
	virtual ~CCrystalHPUI();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void	Cut_HP();
	void	Cal_Pos();
private:
	HRESULT		Add_Component();

private:
	_vec3		Start_Point = { 0.f,0.f,0.f };
	_vec3		m_pTarget_Pos = { 0.f,0.f,0.f };
public:
	static CCrystalHPUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CRcTexLeft*			m_pLBufferCom = nullptr;
private:
	virtual void Free() override;
};

