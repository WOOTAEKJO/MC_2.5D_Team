#pragma once
#include "UI.h"

BEGIN(Engine)

END

class CMeat : public CUI
{
private:
	explicit CMeat(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMeat(const CMeat& rhs);
	virtual ~CMeat();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject(_int iCount);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();

public:
	static CMeat* Create(LPDIRECT3DDEVICE9 pGraphicDev, _int iCount);

private:
	virtual void Free() override;

};

