#pragma once
#include "Engine_Define.h"
#include "CubeItem.h"

class CItemDemoAnimation
{
public:
	explicit CItemDemoAnimation();
	virtual ~CItemDemoAnimation();

public:
	HRESULT				Ready_ItemAnimation(CCubeItem* pCubeItem);
	CItemDemoAnimation* Update_ItemAnimation(CCubeItem* pCubeItem, const float& fTimeDelta);
public:
	void	Update_Matrix(CCubeItem* pCubeItem, const _int& iIndex, vector<FRAME*>& vecFrame);
private:
	FRAME* m_pFrame = nullptr;

	_ulong				m_FrameCount;
	_float				m_fTotalFrameCount;
	_float				m_fStateFrame;
	_float				m_fSpeed;

private:
	//_vec3				m_vParts[PARTS_END][2];
public:
	static	CItemDemoAnimation* Create(CCubeItem* pCubeItem);
public:
	void Free(CCubeItem* statePlayer);

};

