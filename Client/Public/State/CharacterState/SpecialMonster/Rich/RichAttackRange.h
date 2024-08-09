#pragma once
#include "Effect.h"
class CRichAttackRange :
    public CEffect
{
private:
	explicit CRichAttackRange(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRichAttackRange(const CRichAttackRange& rhs);
	virtual ~CRichAttackRange();

public:
	virtual void Render_GameObject() override;
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
public:
	void	Set_OwnerTrans(CTransform* pTrans) { m_OwnerTransform = pTrans; }
private:
	HRESULT		Add_Component();

public:
	static CRichAttackRange* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	_float	m_fCount = 0.f;
	CTransform* m_OwnerTransform = nullptr;
private:
	virtual void Free() override;
};

