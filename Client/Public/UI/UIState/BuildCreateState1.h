#pragma once
#include "UIState.h"
class CBuildCreateState1 :
    public CUIState
{
private:
	explicit	CBuildCreateState1();
	virtual		~CBuildCreateState1();
public:
	virtual HRESULT Ready_State(CUI* pUI);
	virtual CUIState* Update_State(CUI* pUI, const float& fTimeDelta);
public:
	static  CBuildCreateState1* Create(CUI* pUI);
private:
	//SQUARD_ID	eSquadType = SQUARD_ID_END;
private:
	virtual void Free(CUI* pUI);
};

