#include "stdafx.h"
#include "..\Header\Charger.h"
#include "Export_System.h"
#include "Export_Utility.h"

#include "BlockMap.h"

#include "NonWeaponState.h"
#include "ChargerIDLE.h"
CCharger::CCharger(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CCharger::CCharger(const CCharger& rhs)
	: CMonster(rhs)
{
}

CCharger::~CCharger()
{
}

HRESULT CCharger::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CMonster::SetUp_Parts(
		L"Proto_ZombieHeadTexture"
		, L"Proto_ZombieBodyTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieLegTexture"
		, L"Proto_ZombieLegTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieArmTexture"

	), E_FAIL);

	//FAILED_CHECK_RETURN(CMonster::Default_Ratio(), E_FAIL);
	//FAILED_CHECK_RETURN(CMonster::Ready_GameObject(), E_FAIL);
	//FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_vTransform->m_vInfo[INFO_POS].y += 1.f;
	//m_vTransform->Set_Scale(3.f, 3.7f, 1.5f);
	//m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], *m_vTransform->Get_Scale());

	CMonster::Ready_GameObject();

	m_pState = CChargerIDLE::Create(this);
	m_pWeaponState = CNonWeaponState::Create(this);

	m_iHP = 240;
	m_iDamage = 9;
	m_iAttackRange = 30.f;

	m_iCost = CHARGER_COST;

	m_eMonsterType = MOSTERID::CHARGER;

	return S_OK;
}

_int CCharger::Update_GameObject(const _float& fTimeDelta)
{
	CMonster::Ready_Dead();

	CCharacterState* HumanState = m_pState->Update_State(this, fTimeDelta);
	if (HumanState != nullptr)
	{
		HumanState->Free(this);
		Safe_Delete(m_pState);
		m_pState = HumanState;
	}

	m_vTransform = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL];

	Animation_Frame(fTimeDelta);

	LookAt_Target();

	Guide(fTimeDelta);

	Update_Dir_To_Destination();

	return CMonster::Update_GameObject(fTimeDelta);
}

void CCharger::LateUpdate_GameObject()
{

	CMonster::LateUpdate_GameObject();
}

void CCharger::Render_GameObject()
{
	CMonster::Render_GameObject();

}

HRESULT CCharger::Add_Weapon(WEAPONTYPE eWeaponType)
{
	return S_OK;
}

HRESULT CCharger::Add_Component()
{
	return S_OK;
}

void CCharger::OnCollisionEnter(CCollider* _pOther)
{
}

void CCharger::OnCollisionStay(CCollider* _pOther)
{
	if (_pOther->Get_Owner()->Get_ObjectType() == OBJECTTYPE::MONSTER) {
		Pushed(_pOther, 1.f);
	}
}

void CCharger::OnCollisionExit(CCollider* _pOther)
{
}

CCharger* CCharger::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCharger* pInstance = new CCharger(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Skeleton Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCharger::Free()
{
	CMonster::Free();
}
