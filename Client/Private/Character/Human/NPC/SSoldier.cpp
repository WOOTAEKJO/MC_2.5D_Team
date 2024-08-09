#include "stdafx.h"
#include "..\Header\SSoldier.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "SwordState.h"
#include "Sword.h"


CSSoldier::CSSoldier(LPDIRECT3DDEVICE9 pGraphicDev)
	:CHNPC(pGraphicDev)
{
}

CSSoldier::CSSoldier(const CSSoldier& rhs)
	:CHNPC(rhs)
{
}

CSSoldier::~CSSoldier()
{
}

HRESULT CSSoldier::Ready_GameObject()
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

	m_iHP = 100;
	m_iDamage = 5;
	m_iCombat_Power = 5;
	m_iAttackRange = 5.f;
	m_iMaxHP = m_iHP;

	m_iCost = SWORD_SOLDIER_COST;

	return S_OK;
}

_int CSSoldier::Update_GameObject(const _float& fTimeDelta)
{
	CHuman::Ready_Dead();

	if (m_eWeaponType != WEAPONTYPE::SWORD) {
		Safe_Delete(m_pWeaponState);
		m_pWeaponState = CSwordState::Create(this);
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

void CSSoldier::LateUpdate_GameObject()
{
	CHNPC::LateUpdate_GameObject();
}

void CSSoldier::Render_GameObject()
{
	CHNPC::Render_GameObject();

	//_vec2 vPos2 = { 100.f,100.f };
	//_tchar srTest[100] = {};
	//swprintf_s(srTest, L"%d", m_iHP);
	//Engine::Render_Font(L"Font_UI", srTest, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

HRESULT CSSoldier::Add_Weapon(WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CHuman::Add_Weapon(eWeaponType), E_FAIL);

	return S_OK;
}

HRESULT CSSoldier::Add_Component()
{
	return S_OK;
}

CSSoldier* CSSoldier::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSSoldier* pInstance = new CSSoldier(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Skeleton Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSSoldier::Free()
{
	CHNPC::Free();
}
