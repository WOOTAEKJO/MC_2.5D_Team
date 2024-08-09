#pragma once

#include "ControlUI.h"

BEGIN(Engine)

END

class CItemBox : public CControlUI
{
private:
	explicit CItemBox(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CItemBox(const CItemBox& rhs);
	virtual ~CItemBox();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	void	FrameUI_KeyInput();

	virtual	_vec3	Cal_Pos(_int iNum) {

		return  _vec3(m_vTransform->Get_Pos()->x - ((m_vTransform->Get_Scale()->x / 11.7f) * (8 - 2 * iNum)), m_vTransform->Get_Pos()->y, 1.f);
	}

private:
	HRESULT		Add_Component();
public:
	virtual HRESULT	Create_ItemImage() override;
	void		Set_SquadType(SQUARD_ID eType) { m_eSquadType = eType; }
	void		Set_WeaponType(WEAPONTYPE eType) { m_eWeaponType = eType; }
public:
	static CItemBox* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	SQUARD_ID	m_eSquadType = SQUARD_ID_END;
	WEAPONTYPE	m_eWeaponType = WEAPONTYPE::WEAPON_END;
private:
	virtual void Free() override;
};