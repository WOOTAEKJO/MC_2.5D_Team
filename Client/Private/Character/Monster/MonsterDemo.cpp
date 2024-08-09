#include "stdafx.h"
#include "..\Header\MonsterDemo.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "MonsterAnimation.h"

#include "ImGuiMgr.h"

CMonsterDemo::CMonsterDemo(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev), m_pDemo(nullptr)
{
}

CMonsterDemo::CMonsterDemo(const CMonsterDemo& rhs)
	: CMonster(rhs), m_pDemo(rhs.m_pDemo)
{
}

CMonsterDemo::~CMonsterDemo()
{
	
}

HRESULT CMonsterDemo::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CMonster::SetUp_Parts(
		L"Proto_ZombieHeadTexture"
		, L"Proto_ZombieBodyTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieArmTexture"
		, L"Proto_ZombieLegTexture"
		, L"Proto_ZombieLegTexture",
		L"Proto_SkeletonHeadTexture",
		L"Proto_SkeletonHeadTexture",
		L"Proto_SkeletonHeadTexture",
		L"Proto_SkeletonHeadTexture",
		L"Proto_SkeletonHeadTexture",
		L"Proto_SkeletonHeadTexture"), E_FAIL);
	FAILED_CHECK_RETURN(CMonster::Default_Ratio(), E_FAIL);

	m_pDemo = CMonsterAnimation::Create(this, L"IDLE");
	FAILED_CHECK_RETURN(Add_State(), E_FAIL);

	m_pVecFrame = CImGuiMgr::GetInstance()->Get_MonParts();

	m_iHP = 100;

	return S_OK;
}

_int CMonsterDemo::Update_GameObject(const _float& fTimeDelta)
{

	

	m_pDemo->Update_Animation(this, fTimeDelta);

	return CMonster::Update_GameObject(fTimeDelta);
}

void CMonsterDemo::LateUpdate_GameObject()
{

	//CHuman::Height_On_Terrain(false);
	CMonster::LateUpdate_GameObject();
}

void CMonsterDemo::Render_GameObject()
{
	CMonster::Render_GameObject();
}

HRESULT CMonsterDemo::Add_State()
{
	m_pDemo->Add_State(L"IDLE");

	return S_OK;
}

CMonsterDemo* CMonsterDemo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonsterDemo* pInstance = new CMonsterDemo(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMonsterDemo::Free()
{
	m_pDemo->Free(this);
	Safe_Delete(m_pDemo);
	CMonster::Free();
}

