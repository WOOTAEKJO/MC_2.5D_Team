#include "stdafx.h"
#include "..\Header\ZombieSummoner.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "SaveLoadMgr.h"
#include "EventMgr.h"

#include "Zombie.h"
#include "Skeleton.h"
#include "Charger.h"
#include "Ghost.h"

#include "SummonCircle.h"

CZombieSummoner::CZombieSummoner(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCubeItem(pGraphicDev)
{
}

CZombieSummoner::CZombieSummoner(const CZombieSummoner& rhs)
	: CCubeItem(rhs)
{
}

CZombieSummoner::~CZombieSummoner()
{
}

HRESULT CZombieSummoner::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Default_Component(*CSaveLoadMgr::GetInstance()->Get_ItemPartsInfoData(L"GENERATION")), E_FAIL);

	m_iHP = 100.f;

	return S_OK;
}

_int CZombieSummoner::Update_GameObject(const _float& fTimeDelta)
{

	Add_Count(fTimeDelta);

	if (m_fTime > 3.f) {

		/*if ( 3 <= m_iOrder + 1) {
			m_iOrder = 0;
		}
		else {
			m_iOrder += 1;
		}*/
		m_iOrder = rand() % 5;

		Zombie_Summons();
		m_fTime = 0.f;
	}

	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CZombieSummoner::LateUpdate_GameObject()
{
	CCubeItem::LateUpdate_GameObject();
}

void CZombieSummoner::Render_GameObject()
{
	//CCubeItem::Render_GameObject();
}

void CZombieSummoner::Zombie_Summons()
{
	_vec3 vPos = *m_vTransform->Get_Pos();
	

	switch (m_iOrder)
	{
	case 0:
		vPos = vPos;
		break;
	case 1:
		if (vPos.x + vPos.z < 200.f) {
			if (vPos.x > vPos.z) {
				vPos.x += 10.f;
			}
			else {
				vPos.z += 10.f;
			}
		}
		else {
			if (vPos.x > vPos.z) {
				vPos.z += 10.f;
			}
			else {
				vPos.x += 10.f;
			}
		}
		break;
	case 2:
		if (vPos.x + vPos.z < 200.f) {
			if (vPos.x > vPos.z) {
				vPos.x -= 10.f;
			}
			else {
				vPos.z -= 10.f;
			}
		}
		else {
			if (vPos.x > vPos.z) {
				vPos.z -= 10.f;
			}
			else {
				vPos.x -= 10.f;
			}
		}
		break;
	case 3:
		if (vPos.x + vPos.z < 200.f) {
			if (vPos.x > vPos.z) {
				vPos.x = 85.f;
				vPos.z = 75.f;
			}
			else {
				vPos.x = 75.f;
				vPos.z = 145.f;
			}
		}
		else {
			if (vPos.x > vPos.z) {
				vPos.x = 155.f;
				vPos.z = 145.f;
			}
			else {
				vPos.x = 85.f;
				vPos.z = 155.f;
			}
		}
		break;
	case 4:
		if (vPos.x + vPos.z < 200.f) {
			if (vPos.x > vPos.z) {
				vPos.x = 145.f;
				vPos.z = 75.f;
			}
			else {
				vPos.x = 75.f;
				vPos.z = 85.f;
			}
		}
		else {
			if (vPos.x > vPos.z) {
				vPos.x = 155.f;
				vPos.z = 85.f;
			}
			else {
				vPos.x = 145.f;
				vPos.z = 155.f;
			}
		}
		break;
	default:
		return;
	}

	CObjCreationMgr::GetInstance()->Create<CGhost>(OBJECTTYPE::MONSTER,
		vPos, _vec3(117.f, 5.f, 117.f));
	_vec3 vScale = {2.f,2.f,2.f};
	vPos.y -= 3.5f;
	CGameObject* pEffect = CObjCreationMgr::GetInstance()->Create_UI<CSummonCircle>(OBJECTTYPE::EFFECT, vPos
		, vScale);
	pEffect->Get_Transform()->m_vAngle.x = D3DXToRadian(90.f);
	
}

void CZombieSummoner::Init_Pos(const _vec3& vPos)
{
	m_vTransform->Set_Pos(vPos);
}

HRESULT CZombieSummoner::Add_Component()
{
	return S_OK;
}

CZombieSummoner* CZombieSummoner::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CZombieSummoner* pInstance = new CZombieSummoner(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Generator Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CZombieSummoner::Free()
{
	/*for_each(m_vecMonsterInfo.begin(), m_vecMonsterInfo.end(), CDeleteObj2());
	m_vecMonsterInfo.clear();*/

	CCubeItem::Free();
}
