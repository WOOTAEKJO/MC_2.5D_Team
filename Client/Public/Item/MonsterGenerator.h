#pragma once
#include "CubeItem.h"

BEGIN(Engine)


END

class CMonsterGenerator :
    public CCubeItem
{
private:
	explicit CMonsterGenerator(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMonsterGenerator(const CMonsterGenerator& rhs);
	virtual ~CMonsterGenerator();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

private:
	virtual HRESULT	Add_Component();
public:
	static	CMonsterGenerator* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	void	Add_Count(const _float& fTimeDelta) { m_fTime += fTimeDelta; }
private:
	_float		m_fTime = 0.f;							// 시간
	vector<GENERATORINFO*>		m_vecMonsterInfo;		// 몬스터 정보
private:
	virtual void Free();
};

