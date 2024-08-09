#pragma once
#include "ControlUI.h"
class CBuildCreateBoard :
    public CControlUI
{
private:
	explicit CBuildCreateBoard(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBuildCreateBoard(const CBuildCreateBoard& rhs);
	virtual ~CBuildCreateBoard();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void		Set_BuildType(BUILDTYPE eType) { m_eCurType = eType; }
	BUILDTYPE	Get_BuildType() { return m_eCurType; }
public:
	void		Pick_Button(BUILDTYPE eType);
private:

	virtual	_vec3	Cal_Pos(_int iNum) {

		return _vec3(0.f, 0.f, 0.f);
	}

private:
	HRESULT		Add_Component();
public:
	virtual HRESULT	Create_ItemImage() override;
public:
	static CBuildCreateBoard* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	BUILDTYPE	m_eCurType = BUILDTYPE::BUILDTYPE_END;
private:
	_int		m_iBuildCost[9];
private:
	virtual void Free() override;
};

