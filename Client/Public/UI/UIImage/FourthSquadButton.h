#pragma once
#include "UIImage.h"
class CFourthSquadButton :
    public CUIImage
{
private:
	explicit CFourthSquadButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFourthSquadButton(const CFourthSquadButton& rhs);
	virtual ~CFourthSquadButton();

public:
	virtual void Render_GameObject() override;
	HRESULT Ready_GameObject(CUI* pUI);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();
private:
	CUI* m_pUI = nullptr;
	SQUARD_ID	m_eSquadID = SQUARD4;
public:
	static CFourthSquadButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI);

private:
	virtual void Free() override;
};

