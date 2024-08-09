#pragma once
#include "UI.h"

class CControlUI :
    public CUI
{
public:
	enum STATETYPE {TYPE_1, TYPE_2, TYPE_3, TYPE_4, TYPE_5, TYPE_6, TYPE_END};
protected:
	explicit CControlUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CControlUI(const CControlUI& rhs);
	virtual ~CControlUI();

public:
	virtual HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
protected:
	virtual	_vec3	Cal_Pos(_int iNum) PURE;
protected:
	HRESULT		Add_Component() PURE;
public:
	virtual HRESULT	Create_ItemImage() PURE;
	void	Delete_ItemImage();
public:
	void	Mouse_Picking(_vec3* vPickPos);
	_bool	Pick_UI();
	void	Set_StateType(STATETYPE eType) { m_eStateType = eType; }
public:
	void		Set_ChangeType(_bool bCkeck) { m_bChangeType = bCkeck; }
	_bool		Get_ChangeType() { return m_bChangeType; }
protected:
	vector<CGameObject*> m_vecItemImage;
	STATETYPE			 m_eStateType = STATETYPE::TYPE_END;
	_bool				m_bChangeType = false;
protected:
	virtual void Free() override;
};

