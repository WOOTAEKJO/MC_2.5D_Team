#pragma once
#include "UIState.h"
class CItemUIState :
    public CUIState
{
private:
	explicit	CItemUIState();
	virtual		~CItemUIState();
public:
	virtual HRESULT Ready_State(CUI* pUI);
	virtual CUIState* Update_State(CUI* pUI, const float& fTimeDelta);
public:
	static  CItemUIState* Create(CUI* pUI);
private:
	virtual void Free(CUI* pUI);
};

