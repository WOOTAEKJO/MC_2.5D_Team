#pragma once
#include "UIImage.h"
class CBuildHPUI :
    public CUIImage
{
private:
	explicit CBuildHPUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBuildHPUI(const CBuildHPUI& rhs);
	virtual ~CBuildHPUI();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void	Cut_HP();
	void	Cal_Pos();
public:
	void	Set_Owner(CGameObject* pOwner) { m_pOwner = pOwner; }
private:
	HRESULT		Add_Component();

private:
	_vec3			Start_Point = { 0.f,0.f,0.f };
	_vec3			m_pTarget_Pos = { 0.f,0.f,0.f };
	CGameObject*	m_pOwner = nullptr;
public:
	static CBuildHPUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CRcTexLeft* m_pLBufferCom = nullptr;
private:
	virtual void Free() override;
};

