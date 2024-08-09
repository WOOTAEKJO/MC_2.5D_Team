#include "stdafx.h"
#include "..\Header\MageSoldier.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "WandState.h"

CMageSoldier::CMageSoldier(LPDIRECT3DDEVICE9 pGraphicDev)
	:CHNPC(pGraphicDev)
{
}

CMageSoldier::CMageSoldier(const CMageSoldier& rhs)
	: CHNPC(rhs)
{
}

CMageSoldier::~CMageSoldier()
{
}

HRESULT CMageSoldier::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CHuman::SetUp_Parts(
		L"Proto_SSHeadTexture"
		, L"Proto_SSBodyTexture"
		, L"Proto_SSArmTexture"
		, L"Proto_SSArmTexture"
		, L"Proto_SSLegTexture"
		, L"Proto_SSLegTexture"
	), E_FAIL);

	//FAILED_CHECK_RETURN(CHNPC::Ready_GameObject(), E_FAIL);
	//FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_vTransform->m_vInfo[INFO_POS].y -= 1.f;
	//m_vTransform->Set_Scale(1.2f, 2.5f, 1.2f);
	//m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], *m_vTransform->Get_Scale());

	//m_pState = CHNPCIDLE::Create(this);
	//m_pWeaponState = CNonWeaponState::Create(this);

	FAILED_CHECK_RETURN(CHNPC::Ready_GameObject(), E_FAIL);

	m_iHP = 30;
	m_iDamage = 10;
	m_iCombat_Power = 10;
	m_iAttackRange = 40.f;
	m_iMaxHP = m_iHP;

	m_iCost = MAGE_SOLDIER_COST;

	return S_OK;
}

_int CMageSoldier::Update_GameObject(const _float& fTimeDelta)
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

	LookAt_Target();

	Guide(fTimeDelta);

	Update_Dir_To_Destination();

	return CHNPC::Update_GameObject(fTimeDelta);
}

void CMageSoldier::LateUpdate_GameObject()
{
	CHNPC::LateUpdate_GameObject();
}

void CMageSoldier::Render_GameObject()
{
	CHNPC::Render_GameObject();
}

HRESULT CMageSoldier::Add_Weapon(WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CHuman::Add_Weapon(eWeaponType), E_FAIL);

	return S_OK;
}

HRESULT CMageSoldier::Add_Component()
{
	return S_OK;
}

CMageSoldier* CMageSoldier::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMageSoldier* pInstance = new CMageSoldier(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Skeleton Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMageSoldier::Free()
{
	CHNPC::Free();
}
