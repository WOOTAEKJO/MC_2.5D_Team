#include "stdafx.h"
#include "..\Header\Skeleton.h"
#include "Export_System.h"
#include "Export_Utility.h"

#include "BowState.h"
#include "SaveLoadMgr.h"

#include "HMIdle.h"
#include "NonWeaponState.h"

CSkeleton::CSkeleton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CHMonster(pGraphicDev)
{
}

CSkeleton::CSkeleton(const CHMonster& rhs)
	:CHMonster(rhs)
{
}

CSkeleton::~CSkeleton()
{
}

HRESULT CSkeleton::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CHuman::SetUp_Parts(
		L"Proto_SkeletonHeadTexture"
		, L"Proto_SkeletonBodyTexture"
		, L"Proto_SkeletonArmTexture"
		, L"Proto_SkeletonArmTexture"
		, L"Proto_SkeletonLegTexture"
		, L"Proto_SkeletonLegTexture"

	), E_FAIL);

	/*FAILED_CHECK_RETURN(CHuman::Default_Ratio(), E_FAIL);
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_vTransform->m_vInfo[INFO_POS].y -= 1.f;
	m_vTransform->Set_Scale(1.2f, 2.5f, 1.2f);
	m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], *m_vTransform->Get_Scale());*/

	//m_pState = CHMIdle::Create(this);
	//m_pWeaponState = CNonWeaponState::Create(this);

	CHMonster::Ready_GameObject();

	m_iHP = 18;
	m_iDamage = 6;
	m_iAttackRange = 40.f;

	m_iCost = SKELETON_COST;

	m_eMonsterType = MOSTERID::SKELETON;

	return S_OK;
}

_int CSkeleton::Update_GameObject(const _float& fTimeDelta)
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

	LookAt_Target();

	Guide(fTimeDelta);

	Update_Dir_To_Destination();

	return CHMonster::Update_GameObject(fTimeDelta);
}

void CSkeleton::LateUpdate_GameObject()
{
	

	CHMonster::LateUpdate_GameObject();
}

void CSkeleton::Render_GameObject()
{
	CHMonster::Render_GameObject();
}

HRESULT CSkeleton::Add_Weapon(WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CHuman::Add_Weapon(eWeaponType), E_FAIL);

	return S_OK;
}

HRESULT CSkeleton::Add_Component()
{
	return S_OK;
}

HRESULT CSkeleton::Skeleton_Ratio()
{
	m_pTransformCom[TOTAL]->m_vScale.x *= 0.8f;
	m_pTransformCom[TOTAL]->m_vScale.y *= 0.8f;
	m_pTransformCom[TOTAL]->m_vScale.z *= 0.8f;

	m_pTransformCom[HEAD]->m_vScale.x *= 8 / 10.f;
	m_pTransformCom[HEAD]->m_vScale.y *= 8 / 10.f;
	m_pTransformCom[HEAD]->m_vScale.z *= 8 / 10.f;

	m_pTransformCom[BODY]->m_vScale.x *= 8 / 10.f;
	m_pTransformCom[BODY]->m_vScale.y *= 12 / 10.f;
	m_pTransformCom[BODY]->m_vScale.z *= 4 / 10.f;

	m_pTransformCom[LEFT_ARM]->m_vScale.x *= 4 / 10.f;
	m_pTransformCom[LEFT_ARM]->m_vScale.y *= 12 / 10.f;
	m_pTransformCom[LEFT_ARM]->m_vScale.z *= 4 / 10.f;

	m_pTransformCom[RIGHT_ARM]->m_vScale.x *= 4 / 10.f;
	m_pTransformCom[RIGHT_ARM]->m_vScale.y *= 12 / 10.f;
	m_pTransformCom[RIGHT_ARM]->m_vScale.z *= 4 / 10.f;

	m_pTransformCom[LEFT_LEG]->m_vScale.x *= 4 / 10.f;
	m_pTransformCom[LEFT_LEG]->m_vScale.y *= 12 / 10.f;
	m_pTransformCom[LEFT_LEG]->m_vScale.z *= 4 / 10.f;

	m_pTransformCom[RIGHT_LEG]->m_vScale.x *= 4 / 10.f;
	m_pTransformCom[RIGHT_LEG]->m_vScale.y *= 12 / 10.f;
	m_pTransformCom[RIGHT_LEG]->m_vScale.z *= 4 / 10.f;

	Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANIDLE"));

	return S_OK;
}

CSkeleton* CSkeleton::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSkeleton* pInstance = new CSkeleton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Skeleton Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSkeleton::Free()
{
	CHMonster::Free();
}
