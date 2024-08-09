#include "stdafx.h"
#include "MonsterAnimation.h"

#include "ImGuiMgr.h"

CMonsterAnimation::CMonsterAnimation()
	:m_FrameCount(0), m_fTotalFrameCount(0.f), m_fStateFrame(0.f), m_fSpeed(0.f)
{
	//ZeroMemory(&m_vParts, sizeof(_vec3));
}

CMonsterAnimation::~CMonsterAnimation()
{
}

HRESULT CMonsterAnimation::Ready_PlayerState(CMonster* statePlayer, const _tchar* pStateTag)
{
	return S_OK;
}

CMonsterAnimation* CMonsterAnimation::Update_PlayerState(CMonster* statePlayer, const _tchar* pStateTag, const float& fTimeDelta)
{


	return nullptr;
}

void CMonsterAnimation::Update_Animation(CMonster* statePlayer, const float& fTimeDelta)
{
	vector<MONSTERFRAME*> vecFrame;
	_int iFrameIndex = 0;
	if (*CImGuiMgr::GetInstance()->Get_MonMovementFrameCheck()) {
		vecFrame = *CImGuiMgr::GetInstance()->Get_MonMovement();
		iFrameIndex = *CImGuiMgr::GetInstance()->Get_MonMovementFrameIndex();
	}
	else {
		vecFrame = *CImGuiMgr::GetInstance()->Get_MonParts();
		iFrameIndex = *CImGuiMgr::GetInstance()->Get_MonFrameIndex();
	}
	
	m_fSpeed = *CImGuiMgr::GetInstance()->Get_MonSpeed();
	if (*CImGuiMgr::GetInstance()->Get_MonAnimationCheck()) {
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

void CMonsterAnimation::Update_Matrix(CMonster* statePlayer, const _int& iIndex, vector<MONSTERFRAME*>& vecFrame)
{


	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->m_vAngle = D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vRotation);
	//statePlayer->Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vInfo[INFO_POS] = vecFrame[iIndex][(_uint)PARTS::TOTAL].vPosition;
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->m_vInfo[INFO_POS].x = vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vPosition.x;
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->m_vInfo[INFO_POS].y = vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vPosition.y;
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->m_vInfo[INFO_POS].z = vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vPosition.z;
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::HEAD]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::HEAD].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::HEAD]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::HEAD].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::HEAD]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::HEAD].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::BODY]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::BODY].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::BODY]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::BODY].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::BODY]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::BODY].vScale);
	
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_ARM]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_ARM].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_ARM]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_ARM].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_ARM]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_ARM].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_ARM]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_ARM].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_ARM]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_ARM].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_ARM]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_ARM].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_LEG]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_LEG].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_LEG]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_LEG].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_LEG]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_LEG].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_LEG]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_LEG].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_LEG]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_LEG].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_LEG]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_LEG].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC1]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC1].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC1]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC1].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC1]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC1].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC2]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC2].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC2]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC2].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC2]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC2].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC3]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC3].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC3]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC3].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC3]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC3].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC4]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC4].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC4]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC4].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC4]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC4].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC5]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC5].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC5]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC5].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC5]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC5].vScale);

	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC6]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC6].vRotation));
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC6]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC6].vPosition);
	statePlayer->Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC6]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC6].vScale);


}



vector<MONSTERFRAME*> CMonsterAnimation::Find(const _tchar* pStateTag)
{
	auto iter = find_if(m_mapState.begin(), m_mapState.end(), CTag_Finder(pStateTag));

	//if (iter == m_mapState.end())
		//return nullptr;

	return iter->second;
}

void CMonsterAnimation::Add_State(const _tchar* pStateTag)
{
	vector<MONSTERFRAME*> m;

	m_fStateFrame = 60.f;
	m_fSpeed = *CImGuiMgr::GetInstance()->Get_Speed();

	/*FRAME* pFrame = Create_Frame(CImGuiMgr::GetInstance()->Get_Parts());
	NULL_CHECK(pFrame);
	m.push_back(pFrame);*/

	m_mapState.insert({ pStateTag, m });
}

MONSTERFRAME* CMonsterAnimation::Create_Frame(vector<MONSTERFRAME*>* vecPartsFrame)
{
	MONSTERFRAME* pFrame = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];
	ZeroMemory(pFrame, sizeof(MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END]));

	_vec3 d = pFrame[(_uint)MONSTERPARTS::TOTAL].vRotation;

	_vec3 c = (*vecPartsFrame)[(_uint)MONSTERPARTS::TOTAL]->vRotation;



	for (_ulong i = 0; i < (_ulong)PARTS::PARTS_END; i++) {
		pFrame[i] = *(*vecPartsFrame)[i];
	}

	d = pFrame[(_uint)MONSTERPARTS::TOTAL].vRotation;
	return pFrame;
}

CMonsterAnimation* CMonsterAnimation::Create(CMonster* statePlayer, const _tchar* pStateTag)
{
	CMonsterAnimation* pState = new CMonsterAnimation();
	if (FAILED(pState->Ready_PlayerState(statePlayer, pStateTag)))
	{
		Safe_Delete(pState);
		MSG_BOX("PlayerState Create Failed");
		return nullptr;
	}

	return pState;
}

void CMonsterAnimation::Free(CMonster* statePlayer)
{
	for (auto iter : m_mapState) {
		for_each(iter.second.begin(), iter.second.end(), CDeleteArrayObj());
		iter.second.clear();
	}
	m_mapState.clear();
}
