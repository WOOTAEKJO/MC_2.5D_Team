#pragma once
#include "UIImage.h"
class CThirdSquadButton :
    public CUIImage
{
private:
	explicit CThirdSquadButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CThirdSquadButton(const CThirdSquadButton& rhs);
	virtual ~CThirdSquadButton();

public:
	virtual void Render_GameObject() override;
	HRESULT Ready_GameObject(CUI* pUI);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();
private:
	CUI* m_pUI = nullptr;
	SQUARD_ID	m_eSquadID = SQUARD3;
public:
	static CThirdSquadButton* Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI);

private:
	virtual void Free() override;
};

