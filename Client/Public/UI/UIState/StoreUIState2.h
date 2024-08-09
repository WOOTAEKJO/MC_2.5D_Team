#pragma once
#include "UIState.h"
class CStoreUIState2 :
    public CUIState
{
private:
	explicit	CStoreUIState2();
	virtual		~CStoreUIState2();
public:
	virtual HRESULT Ready_State(CUI* pUI);
	virtual CUIState* Update_State(CUI* pUI, const float& fTimeDelta);
public:
	static  CStoreUIState2* Create(CUI* pUI);
private:
	virtual void Free(CUI* pUI);
};

