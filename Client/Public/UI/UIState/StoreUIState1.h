#pragma once
#include "UIState.h"
class CStoreUIState1 :
    public CUIState
{
private:
	explicit	CStoreUIState1();
	virtual		~CStoreUIState1();
public:
	virtual HRESULT Ready_State(CUI* pUI);
	virtual CUIState* Update_State(CUI* pUI, const float& fTimeDelta);
public:
	static  CStoreUIState1* Create(CUI* pUI);
private:
	virtual void Free(CUI* pUI);
};

