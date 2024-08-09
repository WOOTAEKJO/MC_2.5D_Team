#pragma once
#include "UIState.h"
class CItemBoxUIState :
    public CUIState
{
private:
	explicit	CItemBoxUIState();
	virtual		~CItemBoxUIState();
public:
	virtual HRESULT Ready_State(CUI* pUI);
	virtual CUIState* Update_State(CUI* pUI, const float& fTimeDelta);
public:
	static  CItemBoxUIState* Create(CUI* pUI);
private:
	SQUARD_ID	eSquadType = SQUARD_ID_END;
private:
	virtual void Free(CUI* pUI);
};

