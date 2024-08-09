#include "stdafx.h"
#include "..\Header\EventMgr.h"

#include "Export_System.h"
#include "Export_Utility.h"

//#include "Human.h"
//#include "HNPC.h"

#include "Spawner.h"
#include "MonsterSpawner.h"
#include "SoundMgr.h"
#include "AreaMgr.h"

IMPLEMENT_SINGLETON(CEventMgr)

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
	Free();
}

HRESULT CEventMgr::Ready_EventMgr()
{
	return S_OK;
}

void CEventMgr::Update_EventMgr(const _float& fTimeDelta)
{
	Time_Countdown(fTimeDelta);
	if (m_bNextRoundCheck) 
	{
		m_bIsWaveDelay -= fTimeDelta;
		if (m_bIsWaveDelay <= 0)
		{
			if (Engine::CManagement::GetInstance()->Get_GameLogic_Objects(OBJECTTYPE::MONSTER).empty())
			{
				m_bNextRoundCheck = false;
				m_bIsWaveDelay = 20.f;

				CSoundManager::GetInstance()->StopSound(CHANNELID::SOUND_BGM);
				CSoundManager::GetInstance()->PlayBGM(L"Soggy_Swamp.mp3", CHANNELID::SOUND_BGM);
			}

		}
	}


	if (Engine::Key_Down(DIK_M)) {
		Active_Wave();
		m_fTime = 3.f;
	}

}

void CEventMgr::Render_EventMgr()
{
	if (m_fTime > 0.f) 
	{
		_vec2 vPos2 = { 200.f,150.f };
		_tchar srTest[100] = {};
		swprintf_s(srTest, L"ROUND%d", m_iRoundCount);
		Engine::Render_Font(L"Font_Jinji", srTest, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	}
}

void CEventMgr::Ready_Next_Round()
{
	m_bNextRoundCheck = true;
	++m_iRoundCount;
}

void CEventMgr::Active_Wave()
{
	CEventMgr::Ready_Next_Round();

	CSoundManager::GetInstance()->StopSound(CHANNELID::SOUND_BGM);
	CSoundManager::GetInstance()->PlayBGM(L"arena1.mp3", CHANNELID::SOUND_BGM);

	vector<CGameObject*> vMonsterBuildings = CManagement::GetInstance()->Get_GameLogic_Objects(OBJECTTYPE::MONSTER_BUILDING);
	for (CGameObject* pMonsterBuilding : vMonsterBuildings) 
	{
		CMonsterSpawner* spawner = dynamic_cast<CMonsterSpawner*>(pMonsterBuilding);
		if (spawner) 
		{
			spawner->Active_Wave();
		}
	}

	vector<CGameObject*> vMonsters = CManagement::GetInstance()->Get_GameLogic_Objects(OBJECTTYPE::MONSTER);
	for (CGameObject* pMonster : vMonsters)
	{
		CCharacter* monster = dynamic_cast<CCharacter*>(pMonster);
		if (monster)
		{
			monster->Set_PickPos(CAreaMgr::GetInstance()->Get_BeaconPos(CAreaMgr::GetInstance()->Get_AllyOuterAreaIndex()));
		}
	}
}


void CEventMgr::Time_Countdown(const _float& fTimeDelta)
{
	if (m_fTime > fTimeDelta)
	{
		m_fTime -= fTimeDelta;
	}
	else
	{
		m_fTime = 0.f;
	}

}

void CEventMgr::Free()
{
	//for_each(m_vecMonsterInfo.begin(), m_vecMonsterInfo.end(), CDeleteObj2());
	//m_vecMonsterInfo.clear();
}
