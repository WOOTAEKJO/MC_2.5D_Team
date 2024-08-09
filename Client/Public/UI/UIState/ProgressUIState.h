#pragma once
#include "UIState.h"
class CProgressUIState :
    public CUIState
{
private:
	explicit	CProgressUIState();
	virtual		~CProgressUIState();
public:
	virtual HRESULT Ready_State(CUI* pUI);
	virtual CUIState* Update_State(CUI* pUI, const float& fTimeDelta);
public:
	static  CProgressUIState* Create(CUI* pUI);
private:
	//SQUARD_ID	eSquadType = SQUARD_ID_END;
private:
	virtual void Free(CUI* pUI);
};

