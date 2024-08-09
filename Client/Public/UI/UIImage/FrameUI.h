#pragma once
#include "UIImage.h"

BEGIN(Engine)

class CInputDev;

END

class CFrameUI : public CUIImage
{
private:
	explicit CFrameUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFrameUI(const CFrameUI& rhs);
	virtual ~CFrameUI();

private:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;

private:
	HRESULT		Add_Component();

public:
	static CFrameUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;

};

