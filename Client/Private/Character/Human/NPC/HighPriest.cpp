#include "stdafx.h"
#include "..\Header\HighPriest.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "CrossState.h"
#include "NonWeaponState.h"
#include "LeaderIDLE.h"

CHighPriest::CHighPriest(LPDIRECT3DDEVICE9 pGraphicDev)
	:CHNPC(pGraphicDev)
{
}

CHighPriest::CHighPriest(const CHighPriest& rhs)
	: CHNPC(rhs)
{
}

CHighPriest::~CHighPriest()
{
}

HRESULT CHighPriest::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CHuman::SetUp_Parts(
		L"Proto_PHeadTexture"
		, L"Proto_PBodyTexture"
		, L"Proto_PArm2Texture"
		, L"Proto_PArm1Texture"
		, L"Proto_PLeg2Texture"
		, L"Proto_PLeg1Texture"
	), E_FAIL);

	//FAILED_CHECK_RETURN(CHNPC::Ready_GameObject(), E_FAIL);
	//FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_vTransform->m_vInfo[INFO_POS].y -= 1.f;
	//m_vTransform->Set_Scale(1.2f, 2.5f, 1.2f);
	//m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], *m_vTransform->Get_Scale());

	//m_pState = CHNPCIDLE::Create(this);
	//m_pWeaponState = CNonWeaponState::Create(this);

	m_pState = CLeaderIDLE::Create(this);
	m_pWeaponState = CNonWeaponState::Create(this);

	FAILED_CHECK_RETURN(CHuman::Ready_GameObject(), E_FAIL);

	m_iHP = 200;
	m_iDamage = 10;
	m_iCombat_Power = 10;
	m_iAttackRange = 40.f;
	m_iMaxHP = m_iHP;

	m_bIsNotDead = true;

	return S_OK;
}

_int CHighPriest::Update_GameObject(const _float& fTimeDelta)
{
	CHuman::Ready_Dead();

	if (m_eWeaponType != WEAPONTYPE::CROSS) {
		Safe_Delete(m_pWeaponState);
		m_pWeaponState = CCrossState::Create(this);
	}

	CCharacterState* HumanState = m_pState->Update_State(this, fTimeDelta);
	if (HumanState != nullptr)
	{
		HumanState->Free(this);
		Safe_Delete(m_pState);
		m_pState = HumanState;
	}

	m_vTransform = m_pTransformCom[TOTAL];

	Animation_Frame(fTimeDelta);

	if (!m_bSkillRunning) {
		LookAt_Heal_Target();

		Guide(fTimeDelta);

		Update_Dir_To_Destination();
	}


	if (!m_bFullCount) {
		m_fSkillCount += fTimeDelta;

		if (m_fSkillCount > 5.f) {
			m_fSkillCount = 0.f;
			m_bFullCount = true;
		}
	}

	return CHNPC::Update_GameObject(fTimeDelta);
}

void CHighPriest::LateUpdate_GameObject()
{
	CHNPC::LateUpdate_GameObject();
}

void CHighPriest::Render_GameObject()
{
	CHNPC::Render_GameObject();
}

HRESULT CHighPriest::Add_Weapon(WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CHuman::Add_Weapon(eWeaponType), E_FAIL);

	return S_OK;
}

HRESULT CHighPriest::Add_Component()
{
	return S_OK;
}

CHighPriest* CHighPriest::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHighPriest* pInstance = new CHighPriest(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Skeleton Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHighPriest::Free()
{
	CHNPC::Free();
}
