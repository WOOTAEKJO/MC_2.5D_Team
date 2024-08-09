#pragma once
#include "UIImage.h"
class CFirstSquadButton :
    public CUIImage
{
private:
	explicit CFirstSquadButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFirstSquadButton(const CFirstSquadButton& rhs);
	virtual ~CFirstSquadButton();

public:
	virtual void Render_GameObject() override;
	HRESULT Ready_GameObject(CUI* pUI);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();
private:
	CUI* m_pUI = nullptr;
	SQUARD_ID	m_eSquadID = SQUARD1;
public:
	static CFirstSquadButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI);

private:
	virtual void Free() override;
};

