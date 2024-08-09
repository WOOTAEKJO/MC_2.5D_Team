#pragma once
#include "UIImage.h"
class CSecondSquadButton :
    public CUIImage
{
private:
	explicit CSecondSquadButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSecondSquadButton(const CSecondSquadButton& rhs);
	virtual ~CSecondSquadButton();

public:
	virtual void Render_GameObject() override;
	HRESULT Ready_GameObject(CUI* pUI);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();
private:
	CUI* m_pUI = nullptr;
	SQUARD_ID	m_eSquadID = SQUARD2;
public:
	static CSecondSquadButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI);

private:
	virtual void Free() override;
};

