#include "stdafx.h"
#include "..\Header\Player.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "BlockMap.h"

#include "Sword.h"
#include "Bow.h"

#include "NonWeaponState.h"
#include "HIdle.h"

#include "ObjCreationMgr.h"
#include "TestBullet2.h"
#include "TestBullet4.h"

#include "ManagementUI.h"
#include "StoreUI.h"
#include "TestBuilding.h"

#include "SwordFlagpole.h"

#include "CurrentModeMgr.h"
#include "Explosion.h"

#include "SwordMaster.h"
#include "ArchMage.h"
#include "HighPriest.h"
#include "Shooter.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CHuman(pGraphicDev)
	, m_FrameCount(0.f)
	, m_fF(1.f)
{
	//ZeroMemory(m_eState, sizeof(CHumanAnimation));
}

CPlayer::CPlayer(const CPlayer & rhs)
	: CHuman(rhs)
	, m_FrameCount(rhs.m_FrameCount)
	, m_fF(rhs.m_fF)
{
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Add_Component()
{

	CComponent*		pComponent = nullptr;

	return S_OK;
}

void CPlayer::Quick_Move()
{
}

HRESULT CPlayer::Add_Weapon(WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CHuman::Add_Weapon(eWeaponType), E_FAIL);

	return S_OK;
}

CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer *	pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Create Failed");
		return nullptr;
	}
	
	return pInstance;
}

void CPlayer::Free()
{
	CHuman::Free();
}

HRESULT CPlayer::Ready_GameObject()
{
	
	FAILED_CHECK_RETURN(CHuman::SetUp_Parts(
		L"Proto_PlayerHeadTexture"
		, L"Proto_PlayerBodyTexture"
		, L"Proto_PlayerArm1Texture"
		, L"Proto_PlayerArm2Texture"
		, L"Proto_PlayerLeg1Texture"
		, L"Proto_PlayerLeg2Texture"

	), E_FAIL);
	FAILED_CHECK_RETURN(CHuman::Default_Ratio(), E_FAIL);
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_vTransform->m_vInfo[INFO_POS] = {25.f, 3.f, 700.f};

	m_vTransform->m_vInfo[INFO_POS].y -= 1.f;
	m_vTransform->Set_Scale(1.2f, 2.5f, 1.2f);
	m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], *m_vTransform->Get_Scale());

	m_vPickPos = *m_vTransform->Get_Pos() + _vec3(0.f, 3.4f, 0.f);

	m_pState = CHIdle::Create(this);
	m_pWeaponState = CNonWeaponState::Create(this);

	m_iHP = 1000000;
	m_iDamage = 5;
	m_iCombat_Power = 100;
	m_iMaxHP = m_iHP;

	m_bIsNotDead = true;
	m_fSpeed = 10.f;


	return S_OK;
}

Engine::_int CPlayer::Update_GameObject(const _float& fTimeDelta)
{
	//CObjCreationMgr::GetInstance()->Create_Effect<CExplosion>(*m_vTransform->Get_Pos());

	Animation_Frame(fTimeDelta);
	m_vTransform = m_pTransformCom[TOTAL];

	CCharacterState* HumanState = m_pState->Update_State(this,fTimeDelta);
	if (HumanState != nullptr)
	{
		HumanState->Free(this);
		Safe_Delete(m_pState);
		m_pState = HumanState;
	}

	CWeaponState* WeaponState = m_pWeaponState->Update_State(this, fTimeDelta);
	if (WeaponState != nullptr)
	{
		Safe_Delete(m_pWeaponState);
		m_pWeaponState = WeaponState;
	}

	Key_Input(fTimeDelta);

	return 	CHuman::Update_GameObject(fTimeDelta);
}

void CPlayer::LateUpdate_GameObject()
{
	CHuman::LateUpdate_GameObject();
}
void CPlayer::Render_GameObject()
{

	CHuman::Render_GameObject();

	
}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	_vec3 vPos, vDir, vRight, vUp;

	m_vTransform->Get_Info(INFO_POS, &vPos);
	m_vTransform->Get_Info(INFO_LOOK, &vDir);
	m_vTransform->Get_Info(INFO_RIGHT, &vRight);
	m_vTransform->Get_Info(INFO_UP, &vUp);

	if (CCurrentModeMgr::GetInstance()->Get_Current_State_ID() == CURRENTSTATEID::NORMAL) 
	{
		if (CInputDev::GetInstance()->Key_Down(DIK_Z))
		{
			_vec3 vTarget = m_vTransform->m_vInfo[INFO_LOOK] * 5.f;
			m_vPickPos = m_vTransform->m_vInfo[INFO_POS] + vTarget * 2.5f;
			m_pRigidBody->Add_Force(vTarget);
		}

		if (CInputDev::GetInstance()->Key_Down(DIK_X))
		{
			_vec3 vTarget = m_vTransform->m_vInfo[INFO_LOOK] * -12.f;
			//m_vPickPos = m_vTransform->m_vInfo[INFO_POS] + vTarget * 1.5f;
			m_pRigidBody->Add_Force(vTarget);
		}

		if (CInputDev::GetInstance()->Key_Down(DIK_C))
		{
			CObjCreationMgr::GetInstance()->Create_Firework(*m_vTransform->Get_Pos());
		}

		if (Engine::Key_Down(DIK_7)) {
			CObjCreationMgr::GetInstance()->Create_Bullet_Multi<CTestBullet2>(this);
		}

		if (Engine::Key_Down(DIK_8)) {
			CObjCreationMgr::GetInstance()->Create_Bullet_Omnidirection<CTestBullet4>(this);
		}

		if (CSquardMgr::GetInstance()->Get_SelectedSquard() == SQUARD_ID::SQUARD_ID_END) 
		{
			if (Engine::CInputDev::GetInstance()->Mouse_Down(DIM_LB))
			{
				CHuman::Set_Destination();
			}
		}

	}
	  

	if (!Is_Arrived())
	{
		CHuman::Move(fTimeDelta);
	}


	if (Engine::Key_Down(DIK_B)) {
		if (m_pManagementUI == nullptr) {
			m_pManagementUI = CObjCreationMgr::GetInstance()->Create_UI<CManagementUI>(OBJECTTYPE::UI, _vec3(-40.f, 0.f, 1.f), _vec3(350.f, 250.f, 1.f));
			CSquardMgr::GetInstance()->Set_SelectedSquard(SQUARD_ID::SQUARD_ID_END);
			CCurrentModeMgr::GetInstance()->Set_Current_State_ID(CURRENTSTATEID::UIMODE);
		}
		else {
			m_pManagementUI->Set_Dead();
			m_pManagementUI = nullptr;
			CCurrentModeMgr::GetInstance()->Set_Current_State_ID(CURRENTSTATEID::NORMAL);
			CCurrentModeMgr::GetInstance()->Mouse_Fix(false);
			//CFlexibleDynamicCamera* camera = dynamic_cast<CFlexibleDynamicCamera*>(CManagement::GetInstance()->Get_Environment_Objects(OBJECTTYPE::DYNAMIC_CAMERA).front());
			//if (camera) camera->Set_Fix(false);

		}
	}

	
	/*if (m_pManagementUI != nullptr && m_pManagementUI->Get_Dead() == true) {
		m_pManagementUI = nullptr;
	}*/
	

	

	if (Engine::Key_Down(DIK_T)) {
		if (m_pTest == nullptr || m_pTest->Get_Dead()) {
			m_pTest = CObjCreationMgr::GetInstance()->Create_SquardCommander<CSwordMaster>(_vec3(70.f, 5.f, 0.f), _vec3(50.f, 3.f, 50.f));
		}
	}
	if (Engine::Key_Down(DIK_Y)) {
		if (m_pTest == nullptr || m_pTest->Get_Dead()) {
			m_pTest = CObjCreationMgr::GetInstance()->Create_SquardCommander<CArchMage>(_vec3(70.f, 5.f, 0.f), _vec3(50.f, 3.f, 50.f));
		}
	}
	if (Engine::Key_Down(DIK_U)) {
		if (m_pTest == nullptr || m_pTest->Get_Dead()) {
			m_pTest = CObjCreationMgr::GetInstance()->Create_SquardCommander<CHighPriest>(_vec3(70.f, 5.f, 0.f), _vec3(50.f, 3.f, 50.f));
			
		}
	}
	if (Engine::Key_Down(DIK_K)) {
		if (m_pTest == nullptr || m_pTest->Get_Dead()) {
			m_pTest = CObjCreationMgr::GetInstance()->Create_SquardCommander<CShooter>(_vec3(70.f, 5.f, 0.f), _vec3(50.f, 3.f, 50.f));

		}
	}
	if (Engine::Key_Down(DIK_J)) {
		if (m_pTest != nullptr) {
			m_pTest->Set_Dead();
		}
	}
		
	Update_Dir_To_Destination();
}




