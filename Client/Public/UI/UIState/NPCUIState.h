#pragma once
#include "UIState.h"
class CNPCUIState :
    public CUIState
{
private:
	explicit	CNPCUIState();
	virtual		~CNPCUIState();
public:
	virtual HRESULT Ready_State(CUI* pUI) ;
	virtual CUIState* Update_State(CUI* pUI, const float& fTimeDelta) ;
public:
	static  CNPCUIState* Create(CUI* pUI);
private:
	virtual void Free(CUI* pUI);
};

