#pragma once
#include "CubeItem.h"

BEGIN(Engine)

END

class CItemDemo :
	public CCubeItem
{
private:
	explicit CItemDemo(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CItemDemo(const CCubeItem& rhs);
	virtual ~CItemDemo();
public:
	virtual HRESULT Ready_GameObject(ITEMDEMOMODE eMode);
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();
public:
	void	Update_model();

	void	Cube_Create();
	void	Cube_Delete();
	void	Select_Texture();
	void	Mouse_Picking(_vec3* vRayPos, _vec3* vRayDir);

private:
	virtual HRESULT	Add_Component(vector<PARTSITEMINFO*>& vecItemParts);
private:
	_int	m_iPartsNum=0;
	_bool	m_bCheck = true;		// 큐브 생성 관여
	_bool	m_bCheck2 = true;		// 큐브 삭제 관여

	ITEMDEMOMODE m_eMode;
private:
	
public:
	static	CItemDemo* Create(LPDIRECT3DDEVICE9 pGraphicDev, ITEMDEMOMODE eMode);

private:
	virtual void Free();

};

