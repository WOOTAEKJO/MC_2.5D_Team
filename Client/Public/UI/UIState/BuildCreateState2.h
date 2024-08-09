#pragma once
#include "UIState.h"
class CBuildCreateState2 :
    public CUIState
{
private:
	explicit	CBuildCreateState2();
	virtual		~CBuildCreateState2();
public:
	virtual HRESULT Ready_State(CUI* pUI);
	virtual CUIState* Update_State(CUI* pUI, const float& fTimeDelta);
public:
	static  CBuildCreateState2* Create(CUI* pUI);
private:
	//SQUARD_ID	eSquadType = SQUARD_ID_END;
private:
	virtual void Free(CUI* pUI);
};

