#pragma once
#include "UIState.h"
class CETCUIState :
    public CUIState
{
private:
	explicit	CETCUIState();
	virtual		~CETCUIState();
public:
	virtual HRESULT Ready_State(CUI* pUI);
	virtual CUIState* Update_State(CUI* pUI, const float& fTimeDelta);
public:
	static  CETCUIState* Create(CUI* pUI);
private:
	virtual void Free(CUI* pUI);
};

