#include "stdafx.h"
#include "FireBullet.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SaveLoadMgr.h"
#include "ObjCreationMgr.h"

#include "Player.h"

//#include "WindATTCol.h"
#include "FireMagicATTCol.h"

CFireBullet::CFireBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCubeItem(pGraphicDev)
{
}

CFireBullet::CFireBullet(const CFireBullet& rhs)
	: CCubeItem(rhs)
{
}

CFireBullet::~CFireBullet()
{
}

HRESULT CFireBullet::Ready_GameObject(CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"FIREBALL"), E_FAIL);
	FAILED_CHECK_RETURN(CFireBullet::Add_Component(), E_FAIL);

	m_vTransform->Set_Scale(1.f, 1.f, 1.f);

	m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], *m_vTransform->Get_Scale());
	m_vTransform->Set_Scale(0.05f, 0.05f, 0.05f);

	m_iHP = 100.f;

	return S_OK;

}

_int CFireBullet::Update_GameObject(const _float& fTimeDelta)
{
	// Dead 1
	if (m_Owner == nullptr || m_Owner->Get_Dead()) {
		Set_Dead();
		return 0;
	}

	// Time Count
	m_fCount += fTimeDelta;

	// Dead 2
	if (m_fCount > 2.f)
		Set_Dead();

	// Target exception (When Target Dead)
	if (m_pTarget != nullptr && m_pTarget->Get_Dead())
	{
		m_pTarget = nullptr;
	}

	// TargetPos Setting
	if (m_pTarget != nullptr)
	{
		m_vTargetPos = *m_pTarget->Get_Transform()->Get_Pos();

		// Near TargetPos Force Active
		if (Calc_Distance(m_vTargetPos) < 1.f)
		{
			Active_Bullet();
			return CCubeItem::Update_GameObject(fTimeDelta);
		}
	}


	if (m_pTarget == nullptr && m_iTargetSettingCount == 0)
	{
		vector<CGameObject*> monsters = Engine::CManagement::GetInstance()->Get_GameLogic_Objects(OBJECTTYPE::MONSTER);

		_float minDistance = 100;
		for (CGameObject* monster : monsters)
		{
			if (monster == nullptr || monster->Get_Dead()) continue;

			_float fDistance = Calc_Distance(*monster->Get_Transform()->Get_Pos());
			if (fDistance < 30.f)
			{
				if (minDistance > fDistance)
				{
					minDistance = fDistance;
					m_pTarget = monster;
				}
			}
		}
		if (m_pTarget) ++m_iTargetSettingCount;
	}
	

	if (m_pTarget != nullptr && !m_pTarget->Get_Dead())
	{
		_vec3 vDir = m_vTargetPos - *m_vTransform->Get_Pos();
		D3DXVec3Normalize(&vDir, &vDir);

		_float x = vDir.x;
		_float y = vDir.y;
		_float z = vDir.z;

		m_vTransform->m_vAngle.y = atan2f(x, z);

		_vec3 vGroundLook = _vec3(0.f, 1.f, 0.f);

		//_vec3 vTargetLook = vDir;
		//D3DXVec3Normalize(&vTargetLook, &vTargetLook);

		_float fRadian = D3DXVec3Dot(&vGroundLook, &vDir);

		m_vTransform->m_vAngle.x = -fRadian;
	}
	_vec3 vLook = m_vTransform->m_vInfo[INFO_LOOK];
	D3DXVec3Normalize(&vLook, &vLook);
	//vLook.y += 3.f;
	m_vTransform->m_vInfo[INFO_POS] += vLook * m_fSpeed * fTimeDelta;


	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CFireBullet::LateUpdate_GameObject()
{
	CCubeItem::LateUpdate_GameObject();
}

void CFireBullet::Render_GameObject()
{
	CCubeItem::Render_GameObject();
}

void CFireBullet::OnCollisionEnter(CCollider* _pOther)
{
	Active_Bullet();
}

void CFireBullet::OnCollisionStay(CCollider* _pOther)
{
}

void CFireBullet::OnCollisionExit(CCollider* _pOther)
{
}

_float CFireBullet::Calc_Distance(_vec3 targetPos)
{
	_vec3 vDiff = targetPos - *m_vTransform->Get_Pos();
	return sqrt(vDiff.x * vDiff.x + vDiff.y * vDiff.y + vDiff.z * vDiff.z);
}

void CFireBullet::Active_Bullet()
{
	CObjCreationMgr::GetInstance()->Create_ATTColl<CFireMagicATTCol>(0.2f, _vec3(3.f, 3.f, 3.f), 0.f, 20.f, OBJECTTYPE::ALLY_BULLET, this);
	Set_Dead();

}

HRESULT CFireBullet::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });

	for (int i = 0; i < ID_END; ++i)
		for (auto& iter : m_mapComponent[i])
			iter.second->Init_Component(this);

	return S_OK;
}

CFireBullet* CFireBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType)
{
	CFireBullet* pInstance = new CFireBullet(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject(pObj, eParts, eWeaponType))) {
		Safe_Release(pInstance);
		MSG_BOX("FireBullet Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFireBullet::Free()
{
	CCubeItem::Free();
}
