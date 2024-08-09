#pragma once
#include "Effect.h"

class CRichLaser :
    public CEffect
{
private:
	explicit CRichLaser(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRichLaser(const CRichLaser& rhs);
	virtual ~CRichLaser();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
	
public:
	_bool	Get_End_Check() { return m_bCheck; }
private:
	HRESULT		Add_Component();
public:
	static CRichLaser* Create(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	void		Animation_Frame(const _float& fTimeDelta);
private:
	_float		m_fCount = 0.f;
	_bool		m_bCheck = false;
private:
	virtual void Free() override;
};

