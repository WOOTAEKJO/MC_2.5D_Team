#include "stdafx.h"
#include "..\Header\Zombie.h"
#include "Export_System.h"
#include "Export_Utility.h"

CZombie::CZombie(LPDIRECT3DDEVICE9 pGraphicDev)
	:CHMonster(pGraphicDev)
{
}

CZombie::CZombie(const CZombie& rhs)
	: CHMonster(rhs)
{
}

CZombie::~CZombie()
{
}

HRESULT CZombie::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CHuman::SetUp_Parts(
		L"Proto_ZombieHeadTexture"
		, L"Proto_ZombieBodyTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieLegTexture"
		, L"Proto_ZombieLegTexture"

	), E_FAIL);

	//FAILED_CHECK_RETURN(CHuman::Default_Ratio(), E_FAIL);
	//FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_vTransform->m_vInfo[INFO_POS].y -= 1.f;
	//m_vTransform->Set_Scale(1.2f, 2.5f, 1.2f);
	//m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], *m_vTransform->Get_Scale());

	//m_pState = CHMIdle::Create(this);
	//m_pWeaponState = CNonWeaponState::Create(this);

	CHMonster::Ready_GameObject();

	m_iHP = 20;
	m_iDamage = 3;
	m_iAttackRange = 5.f;

	m_iCost = ZOMBIE_COST;

	m_eMonsterType = MOSTERID::ZOMBIE;

	return S_OK;
}

_int CZombie::Update_GameObject(const _float& fTimeDelta)
{
	CHuman::Ready_Dead();

	CCharacterState* HumanState = m_pState->Update_State(this, fTimeDelta);
	if (HumanState != nullptr)
	{
		HumanState->Free(this);
		Safe_Delete(m_pState);
		m_pState = HumanState;
	}

	m_vTransform = m_pTransformCom[TOTAL];

	Animation_Frame(fTimeDelta);

	LookAt_Target();

	Guide(fTimeDelta);

	Update_Dir_To_Destination();

	return CHMonster::Update_GameObject(fTimeDelta);
}

void CZombie::LateUpdate_GameObject()
{


	CHMonster::LateUpdate_GameObject();
}

void CZombie::Render_GameObject()
{
	CHMonster::Render_GameObject();

}

HRESULT CZombie::Add_Weapon(WEAPONTYPE eWeaponType)
{
	return S_OK;
}

HRESULT CZombie::Add_Component()
{
	return S_OK;
}

CZombie* CZombie::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CZombie* pInstance = new CZombie(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Skeleton Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CZombie::Free()
{
	CHMonster::Free();
}
