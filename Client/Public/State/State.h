#pragma once
#include "Base.h"
#include "Character.h"
#include "Engine_Define.h"

class CState : public CBase
{
public:
	explicit	CState() {};
	virtual		~CState() {};

public:
	virtual HRESULT Ready_State(CCharacter* pCharacter) PURE;
	virtual CState* Update_State(CCharacter* pCharacter, const float& fTimeDelta) PURE;

public:
	virtual void Free() {};
};

