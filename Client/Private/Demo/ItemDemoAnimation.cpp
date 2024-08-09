#include "stdafx.h"
#include "..\Header\ItemDemoAnimation.h"

#include "ImGuiMgr.h"
#include "ItemDemo.h"

#include "Export_Utility.h"
#include "Export_System.h"

CItemDemoAnimation::CItemDemoAnimation()
	:m_FrameCount(0), m_fTotalFrameCount(0.f), m_fStateFrame(60.f), m_fSpeed(0.f)
{
}

CItemDemoAnimation::~CItemDemoAnimation()
{
}

HRESULT CItemDemoAnimation::Ready_ItemAnimation(CCubeItem* pCubeItem)
{
	return S_OK;
}

CItemDemoAnimation* CItemDemoAnimation::Update_ItemAnimation(CCubeItem* pCubeItem, const float& fTimeDelta)
{
	
	vector<FRAME*> vecFrame;
	_int iFrameIndex = 0;

	m_fSpeed = *CImGuiMgr::GetInstance()->Get_Speed();
	if (*CImGuiMgr::GetInstance()->Get_AnimationCheck()) {
		if (m_fTotalFrameCount > (m_fStateFrame / m_fSpeed)) {
			if (m_FrameCount > (vecFrame.size() - 1)) {
				m_FrameCount = 0;
			}
			else {
				Update_Matrix(pCubeItem, m_FrameCount, vecFrame);

				m_FrameCount += 1;
			}
			m_fTotalFrameCount = 0.f;
		}
		else {
			m_fTotalFrameCount += 1.f / fTimeDelta;
		}
	}
	else {

		Update_Matrix(pCubeItem, iFrameIndex, vecFrame);

	}

	return nullptr;
}

void CItemDemoAnimation::Update_Matrix(CCubeItem* pCubeItem, const _int& iIndex, vector<FRAME*>& vecFrame)
{
	//Get_Parts_Transform()[(_uint)PARTS::TOTAL]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::TOTAL].vRotation));
	pCubeItem->Get_Transform()->Set_Angle(D3DXToRadian(vecFrame[iIndex]->vRotation));
	pCubeItem->Get_Transform()->Set_Pos(vecFrame[iIndex]->vPosition);
}

CItemDemoAnimation* CItemDemoAnimation::Create(CCubeItem* pCubeItem)
{
	CItemDemoAnimation* pInstance = new CItemDemoAnimation();
	if (FAILED(pInstance->Ready_ItemAnimation(pCubeItem)))
	{
		Safe_Delete(pInstance);
		MSG_BOX("ItemDemoAnimation Create Failed");
		return nullptr;
	}
	
	return pInstance;
}

void CItemDemoAnimation::Free(CCubeItem* statePlayer)
{
}
