#include "stdafx.h"
#include "HumanAnimation.h"

#include "ImGuiMgr.h"

CHumanAnimation::CHumanAnimation()
	:m_FrameCount(0), m_fTotalFrameCount(0.f), m_fStateFrame(0.f), m_fSpeed(0.f)
{
	//ZeroMemory(&m_vParts, sizeof(_vec3));
}

CHumanAnimation::~CHumanAnimation()
{
}

HRESULT CHumanAnimation::Ready_PlayerState(CHuman* statePlayer, const _tchar* pStateTag)
{
	return S_OK;
}

CHumanAnimation* CHumanAnimation::Update_PlayerState(CHuman* statePlayer, const _tchar* pStateTag, const float& fTimeDelta)
{


	return nullptr;
}

void CHumanAnimation::Update_Animation(CHuman* statePlayer, const float& fTimeDelta)
{
	vector<FRAME*> vecFrame;
	_int iFrameIndex = 0;
	if (*CImGuiMgr::GetInstance()->Get_MovementFrameCheck()) {
		vecFrame = *CImGuiMgr::GetInstance()->Get_Movement();
		iFrameIndex = *CImGuiMgr::GetInstance()->Get_MovementFrameIndex();
	}
	else {
		vecFrame = *CImGuiMgr::GetInstance()->Get_Parts();
		iFrameIndex = *CImGuiMgr::GetInstance()->Get_FrameIndex();
	}

	m_fSpeed = *CImGuiMgr::GetInstance()->Get_Speed();
	if (*CImGuiMgr::GetInstance()->Get_AnimationCheck()) {
		if (m_fTotalFrameCount > (m_fStateFrame / m_fSpeed)) {
			if (m_FrameCount > (vecFrame.size() - 1)) {
				m_FrameCount = 0;
				//Add_State(pStateTag, m_fStateFrame,m_fSpeed);
			}
			else {
				Update_Matrix(statePlayer, m_FrameCount, vecFrame);

				m_FrameCount += 1;
			}
			m_fTotalFrameCount = 0.f;
		}
		else {
			m_fTotalFrameCount += 1.f / fTimeDelta;
		}
	}
	else {



		Update_Matrix(statePlayer, iFrameIndex, vecFrame);

	}
}

void CHumanAnimation::Update_Matrix(CHuman* statePlayer, const _int& iIndex, vector<FRAME*>& vecFrame)
{
	statePlayer->Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vAngle = D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::TOTAL].vRotation);
	//statePlayer->Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vInfo[INFO_POS] = vecFrame[iIndex][(_uint)PARTS::TOTAL].vPosition;
	statePlayer->Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vInfo[INFO_POS].x = vecFrame[iIndex][(_uint)PARTS::TOTAL].vPosition.x;
	statePlayer->Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vInfo[INFO_POS].y = vecFrame[iIndex][(_uint)PARTS::TOTAL].vPosition.y;
	statePlayer->Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vInfo[INFO_POS].z = vecFrame[iIndex][(_uint)PARTS::TOTAL].vPosition.z;

	statePlayer->Get_Parts_Transform()[(_uint)PARTS::HEAD]->m_vAngle = D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::HEAD].vRotation);
	statePlayer->Get_Parts_Transform()[(_uint)PARTS::HEAD]->m_vInfo[INFO_POS] = vecFrame[iIndex][(_uint)PARTS::HEAD].vPosition;

	statePlayer->Get_Parts_Transform()[(_uint)PARTS::BODY]->m_vAngle = D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::BODY].vRotation);
	statePlayer->Get_Parts_Transform()[(_uint)PARTS::BODY]->m_vInfo[INFO_POS] = vecFrame[iIndex][(_uint)PARTS::BODY].vPosition;

	statePlayer->Get_Parts_Transform()[(_uint)PARTS::LEFT_ARM]->m_vAngle = D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::LEFT_ARM].vRotation);
	statePlayer->Get_Parts_Transform()[(_uint)PARTS::LEFT_ARM]->m_vInfo[INFO_POS] = vecFrame[iIndex][(_uint)PARTS::LEFT_ARM].vPosition;

	statePlayer->Get_Parts_Transform()[(_uint)PARTS::RIGHT_ARM]->m_vAngle = D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::RIGHT_ARM].vRotation);
	statePlayer->Get_Parts_Transform()[(_uint)PARTS::RIGHT_ARM]->Set_Pos(vecFrame[iIndex][(_uint)PARTS::RIGHT_ARM].vPosition);

	statePlayer->Get_Parts_Transform()[(_uint)PARTS::LEFT_LEG]->m_vAngle = D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::LEFT_LEG].vRotation);
	statePlayer->Get_Parts_Transform()[(_uint)PARTS::LEFT_LEG]->m_vInfo[INFO_POS] = vecFrame[iIndex][(_uint)PARTS::LEFT_LEG].vPosition;

	statePlayer->Get_Parts_Transform()[(_uint)PARTS::RIGHT_LEG]->m_vAngle = D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::RIGHT_LEG].vRotation);
	statePlayer->Get_Parts_Transform()[(_uint)PARTS::RIGHT_LEG]->m_vInfo[INFO_POS] = vecFrame[iIndex][(_uint)PARTS::RIGHT_LEG].vPosition;
}


vector<FRAME*> CHumanAnimation::Find(const _tchar* pStateTag)
{
	auto iter = find_if(m_mapState.begin(), m_mapState.end(), CTag_Finder(pStateTag));

	//if (iter == m_mapState.end())
		//return nullptr;

	return iter->second;
}

void CHumanAnimation::Add_State(const _tchar* pStateTag)
{
	vector<FRAME*> m;

	m_fStateFrame = 60.f;
	m_fSpeed = *CImGuiMgr::GetInstance()->Get_Speed();

	/*FRAME* pFrame = Create_Frame(CImGuiMgr::GetInstance()->Get_Parts());
	NULL_CHECK(pFrame);
	m.push_back(pFrame);*/

	m_mapState.insert({ pStateTag, m });
}

FRAME* CHumanAnimation::Create_Frame(vector<FRAME*>* vecPartsFrame)
{
	FRAME* pFrame = new FRAME[(_uint)PARTS::PARTS_END];
	ZeroMemory(pFrame, sizeof(FRAME[(_uint)PARTS::PARTS_END]));

	_vec3 d = pFrame[(_uint)PARTS::TOTAL].vRotation;

	_vec3 c = (*vecPartsFrame)[(_uint)PARTS::TOTAL]->vRotation;



	for (_ulong i = 0; i < (_ulong)PARTS::PARTS_END; i++) {
		pFrame[i] = *(*vecPartsFrame)[i];
	}

	/*pFrame[TOTAL].vPosition = (*vecPartsFrame)[TOTAL]->vPosition;
	pFrame[TOTAL].vRotation = (*vecPartsFrame)[TOTAL]->vRotation;

	pFrame[HEAD].vPosition = (*vecPartsFrame)[HEAD]->vPosition;
	pFrame[HEAD].vRotation = (*vecPartsFrame)[HEAD]->vRotation;

	pFrame[BODY].vPosition = (*vecPartsFrame)[BODY]->vPosition;
	pFrame[BODY].vRotation = (*vecPartsFrame)[BODY]->vRotation;

	pFrame[LEFT_ARM].vPosition = (*vecPartsFrame)[LEFT_ARM]->vPosition;
	pFrame[LEFT_ARM].vRotation = (*vecPartsFrame)[LEFT_ARM]->vRotation;

	pFrame[RIGHT_ARM].vPosition = (*vecPartsFrame)[RIGHT_ARM]->vPosition;
	pFrame[RIGHT_ARM].vRotation = (*vecPartsFrame)[RIGHT_ARM]->vRotation;

	pFrame[LEFT_LEG].vPosition = (*vecPartsFrame)[LEFT_LEG]->vPosition;
	pFrame[LEFT_LEG].vRotation = (*vecPartsFrame)[LEFT_LEG]->vRotation;

	pFrame[RIGHT_LEG].vPosition = (*vecPartsFrame)[RIGHT_LEG]->vPosition;
	pFrame[RIGHT_LEG].vRotation = (*vecPartsFrame)[RIGHT_LEG]->vRotation;*/

	d = pFrame[(_uint)PARTS::TOTAL].vRotation;
	return pFrame;
}

CHumanAnimation* CHumanAnimation::Create(CHuman* statePlayer, const _tchar* pStateTag)
{
	CHumanAnimation* pState = new CHumanAnimation();
	if (FAILED(pState->Ready_PlayerState(statePlayer, pStateTag)))
	{
		Safe_Delete(pState);
		MSG_BOX("PlayerState Create Failed");
		return nullptr;
	}

	return pState;
}

void CHumanAnimation::Free(CHuman* statePlayer)
{
	for (auto iter : m_mapState) {
		for_each(iter.second.begin(), iter.second.end(), CDeleteArrayObj());
		iter.second.clear();
	}
	m_mapState.clear();
}
