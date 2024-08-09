#include "stdafx.h"
#include "..\Header\ArchMage.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "WandState.h"
#include "NonWeaponState.h"
#include "LeaderIDLE.h"

CArchMage::CArchMage(LPDIRECT3DDEVICE9 pGraphicDev)
	:CHNPC(pGraphicDev)
{
}

CArchMage::CArchMage(const CArchMage& rhs)
	: CHNPC(rhs)
{
}

CArchMage::~CArchMage()
{
}

HRESULT CArchMage::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CHuman::SetUp_Parts(
		L"Proto_AMHeadTexture"
		, L"Proto_AMBodyTexture"
		, L"Proto_AMArm2Texture"
		, L"Proto_AMArm1Texture"
		, L"Proto_AMLeg2Texture"
		, L"Proto_AMLeg1Texture"
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

	m_iHP = 150;
	m_iDamage = 10;
	m_iCombat_Power = 10;
	m_iAttackRange = 40.f;
	m_iMaxHP = m_iHP;

	m_bIsNotDead = true;

	return S_OK;
}

_int CArchMage::Update_GameObject(const _float& fTimeDelta)
{
	CHuman::Ready_Dead();

	if (m_eWeaponType != WEAPONTYPE::WAND) {
		Safe_Delete(m_pWeaponState);
		m_pWeaponState = CWandState::Create(this);
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
		LookAt_Target();

		Guide(fTimeDelta);

		Update_Dir_To_Destination();
	}



	if (!m_bFullCount) {
		m_fSkillCount += fTimeDelta;

		if (m_fSkillCount > 30.f) {
			m_fSkillCount = 0.f;
			m_bFullCount = true;
		}
	}
	return CHNPC::Update_GameObject(fTimeDelta);
}

void CArchMage::LateUpdate_GameObject()
{
	CHNPC::LateUpdate_GameObject();
}

void CArchMage::Render_GameObject()
{
	CHNPC::Render_GameObject();
}

HRESULT CArchMage::Add_Weapon(WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CHuman::Add_Weapon(eWeaponType), E_FAIL);

	return S_OK;
}

HRESULT CArchMage::Add_Component()
{
	return S_OK;
}

CArchMage* CArchMage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CArchMage* pInstance = new CArchMage(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Skeleton Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CArchMage::Free()
{
	CHNPC::Free();
}
