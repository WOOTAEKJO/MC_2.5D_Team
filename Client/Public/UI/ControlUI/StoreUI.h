#pragma once
#include "ControlUI.h"
class CStoreUI :
    public CControlUI
{
private:
	explicit CStoreUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CStoreUI(const CStoreUI& rhs);
	virtual ~CStoreUI();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
private:

	virtual	_vec3	Cal_Pos(_int iNum) {

		return _vec3(0.f, 0.f, 0.f);
	}

private:
	HRESULT		Add_Component();
public:
	virtual HRESULT	Create_ItemImage() override;
	
public:
	void		Set_SquadType(SQUARD_ID eType) { m_eSquard = eType; }
	SQUARD_ID	Get_SquadType() { return m_eSquard; }
private:
	_int		m_iSoldierPrice[5];
	
private:
	SQUARD_ID	m_eSquard = SQUARD_ID_END;
	_bool		m_bFontRenderCheck[8];
public:
	static CStoreUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

