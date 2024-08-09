#pragma once
#include "UIState.h"
class CBuildUIState :
    public CUIState
{
private:
	explicit	CBuildUIState();
	virtual		~CBuildUIState();
public:
	virtual HRESULT Ready_State(CUI* pUI);
	virtual CUIState* Update_State(CUI* pUI, const float& fTimeDelta);
public:
	static  CBuildUIState* Create(CUI* pUI);
private:
	virtual void Free(CUI* pUI);
};

