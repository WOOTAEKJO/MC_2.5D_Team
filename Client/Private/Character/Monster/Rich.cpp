#include "stdafx.h"
#include "..\Header\Rich.h"
#include "Export_System.h"
#include "Export_Utility.h"

#include "SquardMgr.h"

#include "BlockMap.h"

#include "NonWeaponState.h"
#include "RichIDLE.h"

#include "SoundMgr.h"
#include "ObjCreationMgr.h"
#include "SSoldier.h"

#include "RichPhase1.h"

#include "ZombieSummoner.h"
#include "Crystal.h"

#include "RichAttackRange.h"

#include "BossHPUI.h"
#include "BossGaugeUI.h"
#include "BossNameBox.h"

#include "RichLaser.h"
#include "LaserRange.h"
#include "BossDropEffect.h"

#include "ThunderMagicATTCol.h"

CRich::CRich(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
	
	memset(m_bArrived, false, sizeof(m_bArrived));
	ZeroMemory(m_pSummon, sizeof(m_pSummon));
	ZeroMemory(m_pEffect, sizeof(m_pEffect));
	ZeroMemory(m_pLaserEffect, sizeof(m_pLaserEffect));
	ZeroMemory(m_pUI, sizeof(m_pUI));
}

CRich::CRich(const CRich& rhs)
	: CMonster(rhs)
{
}

CRich::~CRich()
{
}

HRESULT CRich::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CMonster::SetUp_Parts(
		L"Proto_RichHead"
		, L"Proto_RichBody"
		, L"Proto_RichArm"
		, L"Proto_RichArm"
		, L"Proto_RichLeg"
		, L"Proto_RichLeg"
		, L"Proto_RichHead"
		, L"Proto_RichHead"
		, L"Proto_RichHead"
		, L"Proto_RichHead"
		, L"Proto_RichHead"
		, L"Proto_RichHead"

	), E_FAIL);

	FAILED_CHECK_RETURN(CMonster::Default_Ratio(), E_FAIL);
	FAILED_CHECK_RETURN(CMonster::Ready_GameObject(), E_FAIL);
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_vTransform->m_vInfo[INFO_POS].y -= 1.f;
	m_vTransform->Set_Scale(1.2f, 2.5f, 1.2f);
	m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], *m_vTransform->Get_Scale());

	//m_pState = CRichPhase1::Create(this);
	m_pState = CRichIDLE::Create(this);
	m_pWeaponState = CNonWeaponState::Create(this);
	

	m_iHP = 2000;
	m_iDamage = 5;
	m_iAttackRange = 100.f;
	m_iMaxHP = m_iHP;
	
	m_eMonsterType = MOSTERID::RICH;

	m_bDamagable = false;
	//m_bIsNotDead = true;
	//m_bRespawn = true;

	m_bUnDying = true;
	return S_OK;
}

_int CRich::Update_GameObject(const _float& fTimeDelta)
{
	//CMonster::Ready_Dead();

	m_fTimeCount += fTimeDelta;

	if (m_pUI[0] == nullptr) {
		Create_Boss_UI();
	}

	CCharacterState* HumanState = m_pState->Update_State(this, fTimeDelta);
	if (HumanState != nullptr)
	{
		HumanState->Free(this);
		Safe_Delete(m_pState);
		m_pState = HumanState;
	}

	Animation_Frame(fTimeDelta);

	if (Engine::Key_Down(DIK_E)) {
		//m_iHP -= 100.f;
		if (m_pSummon[0] != nullptr) {
			for (_int i = 0; i < 4; i++) {
				if (m_pSummon[i]->Get_ObjectType() == OBJECTTYPE::MONSTER_BUILDING) {
					m_pSummon[i]->Set_Dead();
				}
			}
		}

		//m_vTransform->m_vAngle.y = D3DXToRadian( 45.f);
		
		//LaserRange_Create(CROSS);
		//Laser_Create(EX);
		
		
	}

	if (Engine::Key_Down(DIK_1)) {
		

		//Laser_Create(CROSS);
		//Change_Tex();
		//m_iHP -= 5000.f;
		//Laser_Create(EX);
	}

	if (Engine::Key_Down(DIK_2)) {


		//Laser_Create(CROSS);
		//Change_Tex();
		//m_iHP -= 100.f;
		//Laser_Create(CROSS);
	}

	Is_Dead();
	Is_Phase2();

	m_vTransform = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL];

	return CMonster::Update_GameObject(fTimeDelta);
}

void CRich::LateUpdate_GameObject()
{

	CMonster::LateUpdate_GameObject();
}

void CRich::Render_GameObject()
{

	CMonster::Render_GameObject();

	

}

HRESULT CRich::Add_Weapon(WEAPONTYPE eWeaponType)
{
	return S_OK;
}

HRESULT CRich::Add_Component()
{
	return S_OK;
}

void CRich::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->Get_Owner()->Get_ObjectType() == OBJECTTYPE::MONSTER) {
		static_cast<CCharacter*>(_pOther->Get_Owner())->Cut_HP(9999);

		if (m_fTimeCount > 0.3f) {

			if (m_iGaugeCount < 2) {
				m_iGaugeCount++;

				if (m_iGaugeCount == 2) {
					m_bLaserCheck = true;
				}
			}
			m_fTimeCount = 0.f;
		}

		Pushed(_pOther, 0.f);
	}
}

void CRich::OnCollisionStay(CCollider* _pOther)
{
	/*if (_pOther->Get_Owner()->Get_ObjectType() == OBJECTTYPE::MONSTER) {
		static_cast<CCharacter*>(_pOther->Get_Owner())->Cut_HP(9999);
		if (m_iGaugeCount < 10) {
			m_iGaugeCount++;

			if (m_iGaugeCount == 10) {
				m_bLaserCheck = true;
			}
		}

		Pushed(_pOther, 0.f);
	}*/
}

void CRich::OnCollisionExit(CCollider* _pOther)
{
}

void CRich::Reset_Random_Pos()
{
	m_Random_Pos[0] = *m_vTransform->Get_Pos();
	m_Random_Pos[0].z += 50.f;

	for (int i = 0; i < 11; i++) {
		_matrix matRot;
		_vec3 vDir = m_Random_Pos[i] - *m_vTransform->Get_Pos();
		D3DXVec3Normalize(&vDir, &vDir);

		D3DXMatrixRotationY(&matRot, D3DXToRadian(30.f));
		D3DXVec3TransformCoord(&vDir, &vDir, &matRot);
		m_Random_Pos[i+1] = *m_vTransform->Get_Pos();
		m_Random_Pos[i+1] += vDir * 50.f;
	}

	for (_uint i = (_uint)MONSTERPARTS::ETC1; i < (_uint)MONSTERPARTS::MONSTERPARTS_END; i++) {
		// 본체는 vinfo에서 정보를 가져와도 상관 없지만, 본체를 부모로 두고 있는 파츠들은 월드행렬에서
		// 직접 가져와야 한다. 정보가 불일치해서, 왜 그런지는 모름
		// 순서 문제일 수도?
		m_bArrived[i - 7] = false;
	}

	_int iRNum[12];
	_int iDest, iSour,iTemp;

	for (_int i = 0; i < 12; i++) {
		iRNum[i] = i;
	}

	for (_int i = 0; i < 50; i++) {
		iDest = rand() % 12;
		iSour = rand() % 12;

		iTemp = iRNum[iDest];
		iRNum[iDest] = iRNum[iSour];
		iRNum[iSour] = iTemp;

	}

	for (_int i = 0; i < 6; i++) {

		m_iRIndex[i] = iRNum[i]; // 타겟의 위치를 랜덤으로 배정하기 위해서
	}

	for (_int i = 0; i < 6; i++) {
		m_iETCIndex[i] = i; // 순서대로 들어가게 하기 위해서
	}
	m_iETC_Num = 6;
}

void CRich::ETC_ROT()
{
	//m_pTransformCom[(_uint)MONSTERPARTS::ETC1]->Set_Angle(_vec3(60.f, 60.f, 60.f));
	for (_uint i = 7; i < 13; i++) {
		//m_pTransformCom[i]->Rotation(ROT_X, D3DXToRadian(1.f));
		//m_pTransformCom[i]->Rotation(ROT_Y, D3DXToRadian(60.f));
		m_pTransformCom[i]->Rotation(ROT_Z, D3DXToRadian(60.f));
		//m_pTransformCom[i]->m_vAngle += _vec3{ D3DXToRadian(90.f) ,D3DXToRadian(90.f) ,D3DXToRadian(90.f) };
	}
}

void CRich::ETC_LookAT()
{
	for (_int i = 0; i < m_iETC_Num; i++) {
		ETC_Dir_Turn(m_pTransformCom[m_iETCIndex[i] + 7], &m_Random_Pos[m_iRIndex[i]]);
	}
}


void CRich::ETC_Move(const _float& fTimeDelta,const _float& _fSpeed)
{
	
	for (_int i = 0; i < m_iETC_Num; i++) {
		if (!m_bArrived[i]) {
			_vec3 vLook = m_pTransformCom[m_iETCIndex[i]+7]->m_matWorld.m[2];
			D3DXVec3Normalize(&vLook, &vLook);
			m_pTransformCom[m_iETCIndex[i]+7]->Move_Pos(&vLook, fTimeDelta, _fSpeed);
		}
	}

}

_bool CRich::ETC_Is_Arrived(const _float& fTimeDelta)
{
	
	for (_int i = 0; i <  m_iETC_Num; i++) {
		_vec3 vETCPos = m_pTransformCom[m_iETCIndex[i] + 7]->m_matWorld.m[3];
		_vec3 vDir = m_Random_Pos[m_iRIndex[i]] - vETCPos;
		_float fTDir = (abs(vDir.x) + abs(vDir.y) + abs(vDir.z));
		if (!(fTDir > 7.f)) {
			m_bArrived[i] = true;

			for (_int j = 0; j < m_iETC_Num; j++) {

				if (m_bArrived[j] == false)
					break;

				if (j == (m_iETC_Num-1)) {
					memset(m_bArrived, false, sizeof(m_bArrived));
					return true;
				}
			}
		}
	}

	return false;
}

void CRich::HEAD_Target_Turn()
{
	/*_vec3 vPlayerPos = *Engine::CManagement::GetInstance()->Get_GameLogic_Objects(OBJECTTYPE::PLAYER).front()
		->Get_Transform()->Get_Pos();*/

	_vec3 vPos = m_pTransformCom[(_uint)MONSTERPARTS::HEAD]->m_matWorld.m[3];
	_vec3 vDir = m_Random_Pos[0] - vPos;
	D3DXVec3Normalize(&vDir, &vDir);

	m_pTransformCom[(_uint)MONSTERPARTS::HEAD]->m_vAngle.y = atan2f(vDir.x, vDir.z);

}

void CRich::ETC_Commenders_TargetSet(const _int& iNum)
{
	if (iNum > 6)
		return;

	_int iETC_Index[6];
	_int iDest, iSour, iTemp;

	for (_int i = 0; i < 6; i++) {
		iETC_Index[i] = i;
	}

	for (_int i = 0; i < 50; i++) {
		iDest = rand() % 6;
		iSour = rand() % 6;

		iTemp = iETC_Index[iDest];
		iETC_Index[iDest] = iETC_Index[iSour];
		iETC_Index[iSour] = iTemp;

	}

	for (_int i = 0; i < iNum; i++) {

		_int iComNum = CSquardMgr::GetInstance()->Get_Next_Squard();
		if (iComNum >= 5 || iComNum == 0)
			return;
			
		_int iTarget_Index = rand() % iComNum;

		CCharacter* pCommenders = CSquardMgr::GetInstance()->Get_SquardCommander((SQUARD_ID)iTarget_Index);
		
		if (pCommenders == nullptr|| pCommenders->Get_Dead())
			return;

		m_Random_Pos[i] = *pCommenders->Get_Transform()->Get_Pos(); // 타겟 위치 
		m_iRIndex[i] = i;	// 타겟 위치 인덱스 설정
		m_iETCIndex[i] = iETC_Index[i];	// ETC transform 인덱스 설정
		m_iETC_Num = iNum;				// 사용하는 ETC 개수
	}
}

void CRich::ETC_Dir_Turn(CTransform* vETC, _vec3* vTargetPos )
{
	_vec3 vETC_Pos = vETC->m_matWorld.m[3];
	_vec3 vLookX = vETC->m_matWorld.m[2];
	D3DXVec3Normalize(&vLookX, &vLookX);

	_vec3 vTargetPosX = { vTargetPos->x,vETC_Pos.y ,vTargetPos->z };
	_vec3 vTargetLookX = vTargetPosX - vETC_Pos;
	D3DXVec3Normalize(&vTargetLookX, &vTargetLookX); // 왜 부호가 반대로 나오는지를 모르겠다.
	// 본체에 따라 부호가 반대인지 아닌지를 판단해야 한다.
	vETC->m_vAngle.y = atan2f(vTargetLookX.x, vTargetLookX.z);
	// y 축 조정

	_vec3 vGroundLook = _vec3(0.f, 1.f, 0.f);

	_vec3 vTargetLook = *vTargetPos - vETC_Pos;
	D3DXVec3Normalize(&vTargetLook, &vTargetLook);

	_float fRadian = D3DXVec3Dot(&vGroundLook, &vTargetLook);

	vETC->m_vAngle.x = -fRadian;
}

void CRich::Summoner(const _int& iNum)
{
	if (m_bSummonCheck) {
		Delete_Summoner();

		_int iRIndex = rand() % 4;

		_vec3 vPos[4];
		vPos[0] = { 118.f,5.f,60.f };
		vPos[1] = { 60.f,5.f,118.f };
		vPos[2] = { 118.f,5.f,175.f };
		vPos[3] = { 175.f,5.f,118.f };

		switch (iNum)
		{
		case 1:
		{
			
			for (_int i = 0; i < 4; i++) {
				m_pSummon[i] = CObjCreationMgr::GetInstance()->Create_Item<CZombieSummoner>(OBJECTTYPE::WEAPON,
					vPos[i]);
			}
		}
			break;
		case 2:
		{
			m_pSummon[iRIndex] = CObjCreationMgr::GetInstance()->Create_Item<CZombieSummoner>(OBJECTTYPE::WEAPON,
				vPos[iRIndex]);

			for (_int i = 0; i < 4; i++) {
				if (iRIndex == i)
					continue;

				if (vPos[i].x + vPos[i].z < 200.f) {
					if (vPos[i].x > vPos[i].z) {
						vPos[i].z += 15.f;
					}
					else {
						vPos[i].x += 15.f;
					}
				}
				else {
					if (vPos[i].x > vPos[i].z) {
						vPos[i].x -= 15.f;
					}
					else {
						vPos[i].z -= 15.f;
					}
				}

				//vPos[i].y += 5.f;

				m_pSummon[i] = CObjCreationMgr::GetInstance()->Create_Item<CCrystal>(OBJECTTYPE::MONSTER_BUILDING,
					vPos[i]);
			}
		}
			break;
		default:
			break;
		}
		m_bSummonCheck = false;
	}
}

void CRich::Delete_Summoner()
{
	for (_int i = 0; i < 4; i++) {
		if (m_pSummon[i] == nullptr)
			continue;

		m_pSummon[i]->Set_Dead();
	}
}

_bool CRich::Is_Summon_Dead()
{
	_int iCount = 0;

	for (_int i = 0; i < 4; i++) {

		/*if (m_pSummon[i] == nullptr)
			return false;*/

		if (m_pSummon[i]->Get_Dead())
			iCount++;

		if (iCount == 3) {
			return true;
		}
	}

	return false;
}

void CRich::Create_ETC_Attack_Range()
{
	for (_int i = 0; i < m_iETC_Num; i++) {

		_vec3 vScale = (*m_pTransformCom[m_iETCIndex[i] + 7]->Get_Scale());// * 8.f;

		m_Random_Pos[m_iRIndex[i]].y -= 1.f;

		m_pEffect[i] =CObjCreationMgr::GetInstance()->Create_UI<CRichAttackRange>(OBJECTTYPE::EFFECT, m_Random_Pos[m_iRIndex[i]]
			, vScale);
		m_pEffect[i]->Get_Transform()->m_vAngle.x = D3DXToRadian( 90.f);
		static_cast<CRichAttackRange*>(m_pEffect[i])->Set_OwnerTrans(m_pTransformCom[m_iETCIndex[i] + 7]);
	}
}

void CRich::Delete_ETC_Attack_Range()
{
	for (_int i = 0; i < m_iETC_Num; i++) {
		if (m_pEffect[i] == nullptr)
			continue;

		m_pEffect[i]->Set_Dead();
	}
}

void CRich::ETC_ATTCOL()
{
	for (_int i = 0; i < m_iETC_Num; i++) {
		//CObjCreationMgr::GetInstance()->Create_ATTColl<CMeleeATTCol>(100.f, _vec3(2.5f, 4.f, 6.f), 30.f, 9999.f, OBJECTTYPE::ALLY_BULLET, this);
		CMeleeATTCol* pEffect = CMeleeATTCol::Create(m_pGraphicDev, _vec3(5.f, 5.f, 5.f));
		pEffect->Set_DeadTime(1.f);
		pEffect->Set_Damage(9999.f);

		_vec3 vPos = m_Random_Pos[m_iRIndex[i]];
		//_vec3 vAngle = *m_pLaserEffect[(4 * i) + 1]->Get_Transform()->Get_Angle();
		//vPos.y += 4.f;
		pEffect->Get_Transform()->Set_Pos(vPos);
		//pEffect->Get_Transform()->Set_Angle(vAngle);

		Engine::CManagement::GetInstance()->Add_GameLogic_Object(MONSTER_BULLET, pEffect);
	}
}

void CRich::Create_Boss_UI()
{
	_vec3 vPos = { 10.f,260.f,1.f };
	_vec3 vScale = { 285.f,15.f,1.f };

	m_pUI[0] =  CObjCreationMgr::GetInstance()->Create_UI<CBossHPUI>(OBJECTTYPE::UI, vPos, vScale);

	vPos = { 10.f,245.f,1.f };

	m_pUI[1] = CObjCreationMgr::GetInstance()->Create_UI<CBossGaugeUI>(OBJECTTYPE::UI, vPos, vScale);

	vPos = { -215.f,250.f,1.f };
	vScale = { 30.f,30.f,1.f };

	//m_pUI[2] = CObjCreationMgr::GetInstance()->Create_UI<CBossNameBox>(OBJECTTYPE::UI, vPos, vScale);
	CGameObject* pUI = m_pUI[2] = CBossNameBox::Create(m_pGraphicDev, this);
	pUI->Get_Transform()->Set_Pos(vPos);
	pUI->Get_Transform()->Set_Scale(vScale);
	Engine::CManagement::GetInstance()->Add_UI_Object(UI, pUI);
}

void CRich::Laser_Create(RICHLASERTYPE eType)
{
	for (_int i = 0; i < 4; i++) {
		for (_int j = 0; j < 4; j++) {

			//CGameObject* pLaserEffect;

			_vec3 vRichPos = *m_vTransform->Get_Pos();
			
			_vec3 vScale = { 50.f,40.f,50.f };

			_vec3 vPos = vRichPos; 

			_float fX(0.f), fY(0.f), fZ(0.f);

			vPos.y += m_vTransform->Get_Scale()->y;

			m_pLaserEffect[(i*4) + j] = CObjCreationMgr::GetInstance()->Create_UI<CRichLaser>(OBJECTTYPE::EFFECT, vPos
				, vScale);

			switch (eType)
			{
			case CRich::CROSS:
				if (i % 2 == 0) {
					fX = (i - 1) * 90.f;
					fY = 0.f;
					fZ = -45.f + (j * 45.f);
				}
				else {
					fZ = (i - 2) * 90.f;
					fX = 0.f;
					fY = -45.f + (j * 45.f);
				}

				m_pLaserEffect[(i * 4) + j]->Get_Transform()->m_vAngle.x = D3DXToRadian(fX);
				m_pLaserEffect[(i * 4) + j]->Get_Transform()->m_vAngle.y = D3DXToRadian(fY);
				m_pLaserEffect[(i * 4) + j]->Get_Transform()->m_vAngle.z = D3DXToRadian(fZ);
				break;
			case CRich::EX:
				fX = 90.f;
				fY = -135.f + (90 * i);
				fZ = -45.f + (j * 45.f);

				m_pLaserEffect[(i * 4) + j]->Get_Transform()->m_vAngle.x = D3DXToRadian(fX);
				m_pLaserEffect[(i * 4) + j]->Get_Transform()->m_vAngle.y = D3DXToRadian(fY);
				m_pLaserEffect[(i * 4) + j]->Get_Transform()->Axis_Setting(INFO_LOOK, ROT_Y, fY, fZ);
				break;
			}

		}
	}

	for (_int j = 0; j < 2; j++) {
		for (_int i = 0; i < 30; i++) {
			//CObjCreationMgr::GetInstance()->Create_ATTColl<CThunderMagicATTCol>(1.f, _vec3(3.f, 3.f, 3.f), -100.f, 9999.f, OBJECTTYPE::MONSTER_BULLET, this);
			CThunderMagicATTCol* pEffect = CThunderMagicATTCol::Create(m_pGraphicDev, _vec3(2.5f, 3.f, 2.5f));
			pEffect->Set_DeadTime(0.5f);
			pEffect->Set_Damage(9999.f);
			_vec3 vPos;

			switch (eType)
			{
			case CRich::CROSS:
				if (j % 2 == 0) {
					vPos = *m_vTransform->Get_Pos();
					vPos.x -= 75.f;
					vPos.x += i * 5.f;
				}
				else {
					vPos = *m_vTransform->Get_Pos();
					vPos.z -= 75.f;
					vPos.z += i * 5.f;
				}
				break;
			case CRich::EX:
				if (j % 2 == 0) {
					vPos = *m_vTransform->Get_Pos();
					vPos.z += 50.f;
					vPos.x -= 50.f;
					vPos.x += i * 3.5f;
					vPos.z -= i * 3.5f;
				}
				else {
					vPos = *m_vTransform->Get_Pos();
					vPos.z -= 50.f;
					vPos.x -= 50.f;
					vPos.x += i * 3.5f;
					vPos.z += i * 3.5f;
				}
				break;
		
			}
		
			pEffect->Get_Transform()->Set_Pos(vPos);
			Engine::CManagement::GetInstance()->Add_GameLogic_Object(MONSTER_BULLET, pEffect);
		}
	}

	
}

void CRich::LaserRange_Create(RICHLASERTYPE eType)
{
	for (_int i = 0; i < 4; i++) {
		CGameObject* pLaserEffect;

		_vec3 vRichPos = *m_vTransform->Get_Pos();

		_vec3 vScale = { 1.f,40.f,10.f };

		_vec3 vPos = vRichPos;

		_float fX(0.f), fY(0.f), fZ(0.f);

		vPos.y = 2.f;

		m_pLaserRangeEffect[i] = CObjCreationMgr::GetInstance()->Create_UI<CLaserRange>(OBJECTTYPE::EFFECT, vPos
			, vScale);

		switch (eType)
		{
		case CRich::CROSS:
			if (i % 2 == 0) {
				fX = (i - 1) * 90.f;
				fY = 0.f;
				//fZ = -45.f + (j * 45.f);
			}
			else {
				fZ = (i - 2) * 90.f;
				fX = 0.f;
				fY = 90.f;
			}

			m_pLaserRangeEffect[i]->Get_Transform()->m_vAngle.x = D3DXToRadian(fX);
			m_pLaserRangeEffect[i]->Get_Transform()->m_vAngle.y = D3DXToRadian(fY);
			m_pLaserRangeEffect[i]->Get_Transform()->m_vAngle.z = D3DXToRadian(fZ);
			break;
		case CRich::EX:
			fX = 90.f;
			fY = -135.f + (90 * i);
			//fZ = -45.f + (j * 45.f);

			m_pLaserRangeEffect[i]->Get_Transform()->m_vAngle.x = D3DXToRadian(fX);
			m_pLaserRangeEffect[i]->Get_Transform()->m_vAngle.y = D3DXToRadian(fY);
			//m_pLaserEffect[(i * 4) + j]->Get_Transform()->Axis_Setting(INFO_LOOK, ROT_Y, fY, fZ);
			break;
		}
	}
}

void CRich::Delete_LaserRange()
{
	for (_int i = 0; i < 4; i++) {
		if (m_pLaserRangeEffect[i] != nullptr)
		{
			m_pLaserRangeEffect[i]->Set_Dead();
			m_pLaserRangeEffect[i] = nullptr;
		}
	}
}

_bool CRich::Is_Laser_Animation_End()
{
	_int iCount = 0;
	for (_int i = 0; i < 16; i++) {

		if (m_pLaserEffect[i] == nullptr || m_pLaserEffect[i]->Get_Dead())
			iCount++;

		if (iCount == 15)
			return true;
	}

	return false;
}

void CRich::Is_Dead()
{
	if (!Get_Dead())
		return;

	for (_int i = 0; i < 3; i++) {
		if (m_pUI[i] == nullptr || m_pUI[i]->Get_Dead())
			continue;

		m_pUI[i]->Set_Dead();
		m_pUI[i] = nullptr;
	}

	for (_int i = 0; i < 4; i++) {
		if (m_pSummon[i] == nullptr || m_pSummon[i]->Get_Dead())
			continue;

		m_pSummon[i]->Set_Dead();
		m_pSummon[i] = nullptr;
	}

	for (_int i = 0; 6 < 2; i++) {
		if (m_pEffect[i] == nullptr || m_pEffect[i]->Get_Dead())
			continue;

		m_pEffect[i]->Set_Dead();
		m_pEffect[i] = nullptr;
	}

	for (_int i = 0; i < 16; i++) {
		if (m_pLaserEffect[i] == nullptr || m_pLaserEffect[i]->Get_Dead())
			continue;

		m_pLaserEffect[i]->Set_Dead();
		m_pLaserEffect[i] = nullptr;
	}

	/*for (_int i = 0; i < 4; i++) {
		if (m_pLaserRangeEffect[i] == nullptr || m_pLaserRangeEffect[i]->Get_Dead())
			continue;

		m_pLaserRangeEffect[i]->Set_Dead();
		m_pLaserRangeEffect[i] = nullptr;
	}*/
	
}

void CRich::Is_Phase2()
{
	if (!m_bHPCheck) {
		if (m_iHP <= (m_iMaxHP * 0.5f)) {
			m_ePhaseType = RICHPHASETYPE::PHASE2;
			m_bPhaseChangeCheck = true;
			m_bHPCheck = true;
		}
	}
}

void CRich::Create_Drop_Effect()
{
	for (_int i = 0; i < m_iETC_Num; i++) {

		//_vec3 vScale = (*m_pTransformCom[m_iETCIndex[i] + 7]->Get_Scale());// * 8.f;

		//m_Random_Pos[m_iRIndex[i]].y -= 1.f;

		//m_pEffect[i] = CObjCreationMgr::GetInstance()->Create_UI<CRichAttackRange>(OBJECTTYPE::EFFECT, m_Random_Pos[m_iRIndex[i]]
		//	, vScale);
		//m_pEffect[i]->Get_Transform()->m_vAngle.x = D3DXToRadian(90.f);
		//static_cast<CRichAttackRange*>(m_pEffect[i])->Set_OwnerTrans(m_pTransformCom[m_iETCIndex[i] + 7]);
		m_Random_Pos[m_iRIndex[i]].y -= 1.f;
		CObjCreationMgr::GetInstance()->Create_Effect<CBossDropEffect>(m_Random_Pos[m_iRIndex[i]], 40.f);

		CSoundManager::GetInstance()->StopSound(CHANNELID::SOUND_BOSS_VOICE);
		CSoundManager::GetInstance()->PlaySound(L"Earth1.ogg", CHANNELID::SOUND_BOSS_VOICE, 2.f);
	}

	
}

CRich* CRich::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRich* pInstance = new CRich(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Skeleton Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRich::Free()
{
	CMonster::Free();
}
