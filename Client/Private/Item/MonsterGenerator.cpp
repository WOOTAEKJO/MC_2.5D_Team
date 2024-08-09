#include "stdafx.h"
#include "..\Header\MonsterGenerator.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "SaveLoadMgr.h"
#include "EventMgr.h"

#include "Zombie.h"
#include "Skeleton.h"
#include "Charger.h"

CMonsterGenerator::CMonsterGenerator(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCubeItem(pGraphicDev)
{
}

CMonsterGenerator::CMonsterGenerator(const CMonsterGenerator& rhs)
	:CCubeItem(rhs)
{
}

CMonsterGenerator::~CMonsterGenerator()
{
}

HRESULT CMonsterGenerator::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Default_Component(*CSaveLoadMgr::GetInstance()->Get_ItemPartsInfoData(L"GENERATION")), E_FAIL);

	m_iHP = 100.f;

	return S_OK;
}

_int CMonsterGenerator::Update_GameObject(const _float& fTimeDelta)
{
	
	//if (!(CEventMgr::GetInstance()->Get_MonsterInfo()->empty())) {
	//	_int iMoonsterNum = 0;
	//	if (iMoonsterNum == 0) {
	//		/*vector<GENERATORINFO*> vecTemp = *CEventMgr::GetInstance()->Get_MonsterInfo();
	//		GENERATORINFO* pInfo = nullptr;
	//		for (auto& iter : vecTemp) {
	//			pInfo = new GENERATORINFO;
	//			pInfo->eMonsterID = iter->eMonsterID;
	//			pInfo->iMonsterNum = iter->iMonsterNum;
	//			m_vecMonsterInfo.push_back(pInfo);
	//		}*/
	//		m_vecMonsterInfo = *CEventMgr::GetInstance()->Get_MonsterInfo();
	//	}
	//	iMoonsterNum = Engine::CManagement::GetInstance()->Get_GameLogic_Objects(OBJECTTYPE::MONSTER).size();
	//	if (iMoonsterNum <= 20) {

	//		Add_Count(fTimeDelta);

	//		if (m_fTime > 2.f) {

	//			for (_int i = 0; i < m_vecMonsterInfo.size(); i++) {
	//				_vec3 vPos;
	//				m_vTransform->Get_Info(INFO_POS, &vPos);
	//				_vec3 vTargetPos = { 50.f, 5.f, 50.f };

	//				if (iMoonsterNum >= 20)
	//					break;

	//				switch (m_vecMonsterInfo[i]->eMonsterID)
	//				{
	//				case MOSTERID::ZOMBIE:
	//					for (_int j = 0; j < m_vecMonsterInfo[i]->iLimit; j++) {
	//						if (m_vecMonsterInfo[i]->iMonsterNum > 0) {
	//						
	//							vPos.x = vPos.x - 2.f;
	//							vPos.z = vPos.z - 2.f;
	//							CObjCreationMgr::GetInstance()->Create<CZombie>(OBJECTTYPE::MONSTER, vPos, vTargetPos);
	//							--(m_vecMonsterInfo[i]->iMonsterNum);
	//						}
	//					}
	//					break;
	//				case MOSTERID::SKELETON:
	//					for (_int j = 0; j < m_vecMonsterInfo[i]->iLimit; j++) {
	//						if (m_vecMonsterInfo[i]->iMonsterNum > 0) {
	//							vPos.x = vPos.x + 2.f;
	//							vPos.z = vPos.z + 2.f;
	//							CObjCreationMgr::GetInstance()->Create<CSkeleton>(OBJECTTYPE::MONSTER, vPos, vTargetPos);
	//							--(m_vecMonsterInfo[i]->iMonsterNum);
	//						}
	//					}
	//				case MOSTERID::CHARGER:
	//					//if () {
	//						for (_int j = 0; j < m_vecMonsterInfo[i]->iLimit; j++) {
	//							if (m_vecMonsterInfo[i]->iMonsterNum > 0) {
	//								vPos.x = vPos.x + 5.f;
	//								vPos.z = vPos.z + 5.f;
	//								CObjCreationMgr::GetInstance()->Create<CCharger>(OBJECTTYPE::MONSTER, vPos, vTargetPos);
	//								--(m_vecMonsterInfo[i]->iMonsterNum);
	//							}
	//						}
	//					//}
	//					break;
	//				default:
	//					break;
	//				}

	//			}

	//			m_fTime = 0.f;
	//		}
	//	}
	//}
	
	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CMonsterGenerator::LateUpdate_GameObject()
{
	CCubeItem::LateUpdate_GameObject();
}

void CMonsterGenerator::Render_GameObject()
{
	CCubeItem::Render_GameObject();
}

HRESULT CMonsterGenerator::Add_Component()
{
	return S_OK;
}

CMonsterGenerator* CMonsterGenerator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonsterGenerator* pInstance = new CMonsterGenerator(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Generator Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMonsterGenerator::Free()
{
	/*for_each(m_vecMonsterInfo.begin(), m_vecMonsterInfo.end(), CDeleteObj2());
	m_vecMonsterInfo.clear();*/

	CCubeItem::Free();
}
