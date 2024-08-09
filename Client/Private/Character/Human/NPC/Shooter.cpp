#include "stdafx.h"
#include "..\Header\Shooter.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "BowState.h"
#include "NonWeaponState.h"
#include "LeaderIDLE.h"

#include "ShooterAttack.h"

#include "TestBullet2.h"
#include "GuideArrow.h"

CShooter::CShooter(LPDIRECT3DDEVICE9 pGraphicDev)
	:CHNPC(pGraphicDev)
{
}

CShooter::CShooter(const CShooter& rhs)
	: CHNPC(rhs)
{
}

CShooter::~CShooter()
{
}

HRESULT CShooter::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CHuman::SetUp_Parts(
		L"Proto_SHHeadTexture"
		, L"Proto_SHBodyTexture"
		, L"Proto_SHRArmTexture"
		, L"Proto_SHLArmTexture"
		, L"Proto_SHRLegTexture"
		, L"Proto_SHLLegTexture"
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

_int CShooter::Update_GameObject(const _float& fTimeDelta)
{
	CHuman::Ready_Dead();

	if (m_eWeaponType != WEAPONTYPE::BOW) {
		Safe_Delete(m_pWeaponState);
		m_pWeaponState = CBowState::Create(this);
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

		if (m_fSkillCount > 10.f) {
			m_fSkillCount = 0.f;
			m_bFullCount = true;
		}
	}

	return CHNPC::Update_GameObject(fTimeDelta);
}

void CShooter::LateUpdate_GameObject()
{
	CHNPC::LateUpdate_GameObject();
}

void CShooter::Render_GameObject()
{
	CHNPC::Render_GameObject();
}

HRESULT CShooter::Add_Weapon(WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CHuman::Add_Weapon(eWeaponType), E_FAIL);

	return S_OK;
}

HRESULT CShooter::Add_Component()
{
	return S_OK;
}

void CShooter::Create_Arrow()
{
	
	CCubeItem* bullet = CGuideArrow::Create(m_pGraphicDev,this,PARTS::PARTS_END);
	bullet->Get_Transform()->m_vInfo[INFO_LOOK] = m_vTransform->m_vInfo[INFO_LOOK];
	bullet->Get_Transform()->m_vInfo[INFO_POS] = m_vTransform->m_vInfo[INFO_POS];
	bullet->Get_Transform()->m_vAngle = m_vTransform->m_vAngle;
	bullet->Set_Owner(this);
	Engine::CManagement::GetInstance()->Add_GameLogic_Object(OBJECTTYPE::ALLY_BULLET, bullet);

}

void CShooter::Create_Arrow_Multi()
{

	_ushort n = 5;
	_float angle = 10;

	for (_ushort i = 0; i < n; ++i)
	{
		CCubeItem* bullet = CGuideArrow::Create(m_pGraphicDev, this, PARTS::PARTS_END);
		bullet->Get_Transform()->m_vInfo[INFO_LOOK] = m_vTransform->m_vInfo[INFO_LOOK];
		bullet->Get_Transform()->m_vInfo[INFO_POS] = m_vTransform->m_vInfo[INFO_POS];
		bullet->Get_Transform()->m_vAngle = m_vTransform->m_vAngle;
		bullet->Get_Transform()->m_vAngle.y += D3DXToRadian((i - (n - 1) / 2) * angle);
		bullet->Set_Owner(this);
		Engine::CManagement::GetInstance()->Add_GameLogic_Object(OBJECTTYPE::ALLY_BULLET, bullet);
	}


}

CShooter* CShooter::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CShooter* pInstance = new CShooter(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Skeleton Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShooter::Free()
{
	CHNPC::Free();
}
