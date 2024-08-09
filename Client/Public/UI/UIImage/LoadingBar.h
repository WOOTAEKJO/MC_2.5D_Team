#pragma once
#include "UIImage.h"
class CLoadingBar :
    public CUIImage
{
private:
	explicit CLoadingBar(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLoadingBar(const CLoadingBar& rhs);
	virtual ~CLoadingBar();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void	Cal();

private:
	HRESULT		Add_Component();

private:

	CRcTexLeft* m_pLBufferCom = nullptr;
public:
	static CLoadingBar* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

