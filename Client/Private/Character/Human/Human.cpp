#include "stdafx.h"
#include "..\Header\Human.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "BlockMap.h"
#include "CubeItem.h"
#include "SaveLoadMgr.h"
#include "AStarMgr.h"

#include "Sword.h"
#include "Bow.h"
#include "Arrow.h"

#include "ObjCreationMgr.h"


CHuman::CHuman(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCharacter(pGraphicDev)
	/*, m_FrameCount(0)
	, m_fTotalFrameCount(0.f)
	, m_fFrameSpeed(1.f)
	, m_pState(nullptr)
	, m_vPickPos(0.f, 0.f, 0.f)
	, m_pVecFrame(nullptr)
	, m_bIsRotate(false)*/
{
	memset(m_pBufferCom, 0, sizeof(m_pBufferCom));
	memset(m_pTransformCom, 0, sizeof(m_pTransformCom));
	memset(m_pTextureCom, 0, sizeof(m_pTextureCom));
	memset(m_pCalculatorCom, 0, sizeof(m_pCalculatorCom));
}

CHuman::CHuman(const CHuman& rhs)
	:CCharacter(rhs)
	/*, m_FrameCount(rhs.m_FrameCount)
	, m_fTotalFrameCount(rhs.m_fTotalFrameCount)
	, m_fFrameSpeed(rhs.m_fFrameSpeed)
	, m_pState(rhs.m_pState)
	, m_vPickPos(rhs.m_vPickPos)
	, m_pVecFrame(nullptr)
	, m_bIsRotate(false)*/
{
}

CHuman::~CHuman()
{
}

HRESULT CHuman::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CHuman::Default_Ratio(), E_FAIL);
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_vTransform->m_vInfo[INFO_POS].y -= 1.f;
	m_vTransform->Set_Scale(1.2f, 2.5f, 1.2f);
	m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], *m_vTransform->Get_Scale());

	return S_OK;
}

_int CHuman::Update_GameObject(const _float& fTimeDelta)
{

	m_pTransformCom[HEAD]->m_matParWorld = m_pTransformCom[TOTAL]->m_matWorld;
	m_pTransformCom[BODY]->m_matParWorld = m_pTransformCom[TOTAL]->m_matWorld;
	m_pTransformCom[LEFT_ARM]->m_matParWorld = m_pTransformCom[TOTAL]->m_matWorld;
	m_pTransformCom[RIGHT_ARM]->m_matParWorld = m_pTransformCom[TOTAL]->m_matWorld;
	m_pTransformCom[LEFT_LEG]->m_matParWorld = m_pTransformCom[TOTAL]->m_matWorld;
	m_pTransformCom[RIGHT_LEG]->m_matParWorld = m_pTransformCom[TOTAL]->m_matWorld;

	_vec3 vPos;
	vPos = m_pTransformCom[TOTAL]->m_vInfo[INFO_POS];

	if (m_eObjectType != OBJECTTYPE::HUMAN_DEMO) {
		/*_float fHeight = dynamic_cast<CBlockMap*>(Engine::CManagement::GetInstance()->Get_Environment_Objects(OBJECTTYPE::BLOCKMAP).front())->
			Get_ClosestBelowBlockHeight(vPos.x, vPos.y, vPos.z);

		if (fHeight > 0)
			m_pTransformCom[TOTAL]->m_vInfo[INFO_POS].y = fHeight + 3.4f;*/

		m_pTransformCom[TOTAL]->m_vInfo[INFO_POS].y = 3.4f;
	}

	m_pRigidBody->Update_RigidBody(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 	__super::Update_GameObject(fTimeDelta);
}

void CHuman::LateUpdate_GameObject()
{
	//Height_On_Terrain(true);
	
	__super::LateUpdate_GameObject();
}

void CHuman::Render_GameObject()
{
	
	D3DMATERIAL9			tMtrl;
	ZeroMemory(&tMtrl, sizeof(D3DMATERIAL9));

	tMtrl.Diffuse = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Specular = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Ambient = { m_fMtrl_Ambient[0], m_fMtrl_Ambient[1], m_fMtrl_Ambient[2], m_fMtrl_Ambient[3] };
	tMtrl.Emissive = { 0.f, 0.f, 0.f, 0.f };
	tMtrl.Power = 0.f;
	m_pGraphicDev->SetMaterial(&tMtrl);

	for (_ushort i = HEAD; i < PARTS_END; ++i)
	{

		

		//m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);

		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom[i]->Get_WorldMatrix());
		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
		m_pTextureCom[i]->Render_Textrue(0);
		m_pBufferCom[i]->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		//m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	if (m_eObjectType != OBJECTTYPE::HUMAN_DEMO) {
		m_pCollider->Render_Collider();
	}

	

}	


HRESULT CHuman::SetUp_Parts(const _tchar* Head,
	const _tchar* Body,
	const _tchar* Arm1,
	const _tchar* Arm2,
	const _tchar* Leg1,
	const _tchar* Leg2)
{
	CComponent* pComponent = nullptr;

	// ��ü
	pComponent = m_pTransformCom[TOTAL] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_TOTAL", pComponent });

	pComponent = m_pCalculatorCom[TOTAL] = dynamic_cast<CCalculator*>(Engine::Clone_Proto(L"Proto_Calculator"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Calculator_TOTAL", pComponent });

	//�Ӹ�
	pComponent = m_pBufferCom[HEAD] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_HEAD", pComponent });

	pComponent = m_pTransformCom[HEAD] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_HEAD", pComponent });

	pComponent = m_pTextureCom[HEAD] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Head));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_HEAD", pComponent });

	//����

	pComponent = m_pBufferCom[BODY] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_BODY", pComponent });

	pComponent = m_pTransformCom[BODY] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_BODY", pComponent });

	pComponent = m_pTextureCom[BODY] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Body));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_BODY", pComponent });

	// ����
	pComponent = m_pBufferCom[LEFT_ARM] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_LEFT_ARM", pComponent });

	pComponent = m_pTransformCom[LEFT_ARM] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_LEFT_ARM", pComponent });

	pComponent = m_pTextureCom[LEFT_ARM] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Arm1));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_LEFT_ARM", pComponent });


	// ������
	pComponent = m_pBufferCom[RIGHT_ARM] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_RIGHT_ARM", pComponent });

	pComponent = m_pTransformCom[RIGHT_ARM] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_RIGHT_ARM", pComponent });

	pComponent = m_pTextureCom[RIGHT_ARM] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Arm2));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_RIGHT_ARM", pComponent });


	// �޴ٸ�
	pComponent = m_pBufferCom[LEFT_LEG] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_LEFT_LEG", pComponent });

	pComponent = m_pTransformCom[LEFT_LEG] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_LEFT_LEG", pComponent });

	pComponent = m_pTextureCom[LEFT_LEG] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Leg1));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_LEFT_LEG", pComponent });


	// �����ٸ�
	pComponent = m_pBufferCom[RIGHT_LEG] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_RIGHT_LEG", pComponent });

	pComponent = m_pTransformCom[RIGHT_LEG] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_RIGHT_LEG", pComponent });

	pComponent = m_pTextureCom[RIGHT_LEG] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Leg2));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_RIGHT_LEG", pComponent });


	pComponent = m_vTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });

	pComponent = m_pRigidBody = dynamic_cast<CRigidBody*>(Engine::Clone_Proto(L"Proto_RigidBody"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_RigidBody", pComponent });

	for (int i = 0; i < ID_END; ++i)
		for (auto& iter : m_mapComponent[i])
			iter.second->Init_Component(this);

	return S_OK;
}

HRESULT CHuman::Default_Ratio()
{
	m_pTransformCom[TOTAL]->m_vScale.x *= 1 / 2.f;
	m_pTransformCom[TOTAL]->m_vScale.y *= 1 / 2.f;
	m_pTransformCom[TOTAL]->m_vScale.z *= 1 / 2.f;

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


void CHuman::Animation_Frame(const float& fTimeDelta)
{
	if (nullptr == m_pVecFrame) return;

	if (m_fTotalFrameCount > (1 / fTimeDelta)) {
		if (Is_Animation_Frame_End()) {
			m_FrameCount = 0;
		}
		else {
			Update_Matrix(m_FrameCount, *m_pVecFrame);

			m_FrameCount += 1;
		}
		m_fTotalFrameCount = 0.f;
	}
	else {
		m_fTotalFrameCount += m_fFrameSpeed / fTimeDelta;
	}
}

void CHuman::Update_Matrix(const _int& iIndex, vector<FRAME*>& vecFrame)
{
	
	Animation_Total_Frame_Setting(iIndex, vecFrame);

	//Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vInfo[INFO_POS].y = vecFrame[iIndex][(_uint)PARTS::TOTAL].vPosition.y;

	Get_Parts_Transform()[(_uint)PARTS::HEAD]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::HEAD].vRotation));
	Get_Parts_Transform()[(_uint)PARTS::HEAD]->Set_Pos(vecFrame[iIndex][(_uint)PARTS::HEAD].vPosition);

	Get_Parts_Transform()[(_uint)PARTS::BODY]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::BODY].vRotation));
	Get_Parts_Transform()[(_uint)PARTS::BODY]->Set_Pos(vecFrame[iIndex][(_uint)PARTS::BODY].vPosition);

	Get_Parts_Transform()[(_uint)PARTS::LEFT_ARM]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::LEFT_ARM].vRotation));
	Get_Parts_Transform()[(_uint)PARTS::LEFT_ARM]->Set_Pos(vecFrame[iIndex][(_uint)PARTS::LEFT_ARM].vPosition);

	Get_Parts_Transform()[(_uint)PARTS::RIGHT_ARM]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::RIGHT_ARM].vRotation));
	Get_Parts_Transform()[(_uint)PARTS::RIGHT_ARM]->Set_Pos(vecFrame[iIndex][(_uint)PARTS::RIGHT_ARM].vPosition);

	Get_Parts_Transform()[(_uint)PARTS::LEFT_LEG]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::LEFT_LEG].vRotation));
	Get_Parts_Transform()[(_uint)PARTS::LEFT_LEG]->Set_Pos(vecFrame[iIndex][(_uint)PARTS::LEFT_LEG].vPosition);

	Get_Parts_Transform()[(_uint)PARTS::RIGHT_LEG]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::RIGHT_LEG].vRotation));
	Get_Parts_Transform()[(_uint)PARTS::RIGHT_LEG]->Set_Pos(vecFrame[iIndex][(_uint)PARTS::RIGHT_LEG].vPosition);
}

void CHuman::Animation_Total_Frame_Setting(const _int& iIndex, vector<FRAME*>& vecFrame)
{
	if (m_bIsRotate == false) {
		//m_InitTotPos = *m_pTransformCom[TOTAL]->Get_Pos();
		m_InitTotRot = *m_pTransformCom[TOTAL]->Get_Angle();
		// 초기 값을 ????��.
		
	}
	else {
		//m_pTransformCom[TOTAL]->Set_Pos(m_InitTotPos);
		m_pTransformCom[TOTAL]->Set_Angle(m_InitTotRot);

		//Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vInfo[INFO_POS].y = vecFrame[iIndex][(_uint)PARTS::TOTAL].vPosition.y;
		Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vAngle += D3DXToRadian(vecFrame[iIndex][(_uint)PARTS::TOTAL].vRotation);

	}
	
}





_vec3 CHuman::Picking_On_Terrain()
{
	//BlockMap
	_vec3 vecIntersect(0.f, 0.f, 0.f);
	const list<CBlock*>* pBlockList = dynamic_cast<CBlockMap*>(
		Engine::CManagement::GetInstance()
		->Get_Environment_Objects(OBJECTTYPE::BLOCKMAP).front())
		->Get_BlockListPtr();

	for (auto& pBlock : *pBlockList) {
		vecIntersect = m_pCalculatorCom[TOTAL]->Picking_OnBlockTop(g_hWnd, pBlock->Get_Pos());
		if (_vec3(0.f, 0.f, 0.f) != vecIntersect)
			return vecIntersect;
	}

	return  _vec3(0.f, 0.f, 0.f);
}

void CHuman::Set_Destination()
{
	_vec3 vBuf(0.f, 0.f, 0.f), vZero(0.f, 0.f, 0.f);

	vBuf = Picking_On_Terrain();

	/*Pair	pStart, pDest;

	pStart.first = (m_vTransform->Get_Pos()->x) / 2;
	pStart.second = (m_vTransform->Get_Pos()->z) / 2;

	pDest.first = (vBuf.x) / 2;
	pDest.second = (vBuf.z) / 2; 

	vector<POINT> vecRoute;

	CAStarMgr::GetInstance()->AStar(pStart, pDest, vecRoute);

	Set_Route(vecRoute);

	list<CBlock*> listBlock = *dynamic_cast<CBlockMap*>(Engine::CManagement::GetInstance()->Get_Environment_Objects(OBJECTTYPE::BLOCKMAP).front())
		->Get_BlockList();

	for (auto& iter : listBlock) {
		for (auto& iter2 : m_vecRoute) {
			if (iter->Get_Transform()->Get_Pos()->x == iter2.x   &&
				iter->Get_Transform()->Get_Pos()->z == iter2.y ) {
				iter->Set_BlockCode(1);
			}
		}
	}*/

	if (vBuf != vZero)
		m_vPickPos = vBuf;
}

bool CHuman::Is_Animation_Frame_End()
{
	return m_FrameCount > (m_pVecFrame->size() - 1);
}

//void CHuman::Create_Bullet()
//{
//	CObjCreationMgr::GetInstance()->Create_Bullet<CTestBullet>(this);
//}
//
//void CHuman::Create_Bullet2()
//{
//	CObjCreationMgr::GetInstance()->Create_Bullet_Multi<CTestBullet2>(this);
//}
//
//void CHuman::Create_Bullet3()
//{
//
//	CObjCreationMgr::GetInstance()->Create_Bullet_Meteor<CTestBullet3>(this);
//}

_bool CHuman::Attack_Stance(const _float& fRange)
{
	if (m_bMoveMode) 
	{
		return false;
	}

	if (Is_Target_Dead()) {
		return false;
	}


	if (m_pTarget == nullptr || m_pTarget->Get_Dead())
	{
		return false;
	}

	CTransform* pTargetTransCom = dynamic_cast<CGameObject*>(m_pTarget)->Get_Transform();
	if (pTargetTransCom == nullptr || pTargetTransCom->Get_WorldMatrix() == nullptr)
	{
		return false;
	}

	try 
	{
		_vec3 vDist, vPos, vTargetPos;
		//_float fRadius = 2.7f;

		m_pTransformCom[TOTAL]->Get_Info(INFO_POS, &vPos);
		pTargetTransCom->Get_Info(INFO_POS, &vTargetPos);

		vDist = vPos - vTargetPos;

		_float fX = vDist.x;
		_float fY = vDist.y;
		_float fZ = vDist.z;


		if ((fX * fX + fY * fY + fZ * fZ) <= fRange * fRange) {
			return true;
		}
	}
	catch(_int e)
	{
		return false;
	}
	

	return false;
}

void CHuman::Free()
{
	CCharacter::Free();
}

//void CHuman::Delete_Weapon()
//{
//	if (m_pWeapon != nullptr) {
//		m_pWeapon->Set_Dead();
//	}
//}
//
//void CHuman::Delete_SubWeapon()
//{
//	if (m_pSubWeapon != nullptr)
//		m_pSubWeapon->Set_Dead();
//}
//
//HRESULT CHuman::Add_SubWeapon(WEAPONTYPE eWeaponType)
//{
//	CCubeItem* pGameObject = nullptr;
//
//	if (m_eWeaponType == WEAPONTYPE::BOW) {
//		pGameObject = CArrow::Create(m_pGraphicDev, this, PARTS::RIGHT_ARM);
//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	}
//	OBJECTTYPE eObjType;
//
//	if (m_eObjectType == OBJECTTYPE::PLAYER) {
//		eObjType = OBJECTTYPE::ALLY_BULLET;
//	}
//	else if (m_eObjectType == OBJECTTYPE::MONSTER) {
//		eObjType = OBJECTTYPE::MONSTER_BULLET;
//	}
//	else {
//		return E_FAIL;
//	}
//
//	CManagement::GetInstance()->Add_GameLogic_Object(eObjType, pGameObject);
//	m_pSubWeapon = pGameObject;
//
//	return S_OK;
//}


//HRESULT CHuman::Add_Weapon(WEAPONTYPE eWeaponType)
//{
//	CCubeItem* pGameObject = nullptr;
//	if (eWeaponType == WEAPONTYPE::SWORD) {
//		pGameObject = CSword::Create(m_pGraphicDev, this, RIGHT_ARM);
//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	}
//	if (eWeaponType == WEAPONTYPE::BOW) {
//		pGameObject = CBow::Create(m_pGraphicDev, this, LEFT_ARM);
//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	}
//
//	m_pWeapon = pGameObject;
//	CManagement::GetInstance()->Add_GameLogic_Object(OBJECTTYPE::WEAPON, pGameObject);
//	m_eWeaponType = eWeaponType;
//
//	return S_OK;
//}


//_vec3 CHuman::Calc_Distance_To_Destination()
//{
//	return m_vPickPos - m_vTransform->m_vInfo[INFO_POS];
//}

//bool CHuman::Is_Arrived()
//{
//	_vec3 distance = Calc_Distance_To_Destination();
//	return !(abs(distance.x) + abs(distance.y) + abs(distance.z) > 2.7f);
//}

//void CHuman::Move(const _float& fTimeDelta,const _float& fSpeed)
//{
//	/*if (m_bIsRotate)
//		return;*/
//
//	_vec3	vPos, vDir;
//
//	m_vTransform->Get_Info(INFO_POS, &vPos);
//	vDir = m_vPickPos - vPos;
//
//	D3DXVec3Normalize(&vDir, &vDir);
//	m_vTransform->Move_Pos(&vDir, fTimeDelta, fSpeed);
//	//m_vTransform->m_vAngle.y = atan2f(vDir.x, vDir.z);
//}

//void CHuman::Target_Dir_Update()
//{
//	if (m_pTarget == nullptr || m_pTarget->Get_Dead())
//		return;
//
//	m_pTarget->Get_Transform()->Get_Info(INFO_POS, &m_vPickPos);
//}
//
//



//void CHuman::Create_ATTColl(const _float& fDeadTime, const _vec3& vScale, const _float& fDist, OBJECTTYPE eObjType, CGameObject* pOwner)
//{
//	CGameObject* gameObject = CMeleeATTCol::Create(m_pGraphicDev, vScale);
//	gameObject->Get_Transform()->m_vInfo[INFO_LOOK] = m_vTransform->m_vInfo[INFO_LOOK];
//	_vec3 vDir;
//	_vec3 vTemp = *D3DXVec3Normalize(&vDir, &m_vTransform->m_vInfo[INFO_LOOK]) * fDist;
//	gameObject->Get_Transform()->m_vInfo[INFO_POS] = m_vTransform->m_vInfo[INFO_POS] + vTemp;
//	dynamic_cast<CMeleeATTCol*>(gameObject)->Set_DeadTime(fDeadTime);
//	dynamic_cast<CMeleeATTCol*>(gameObject)->Set_Owner(pOwner);
//	Engine::CManagement::GetInstance()->Add_GameLogic_Object(eObjType, gameObject);
//}
//
//void CHuman::LookAt_Target()
//{
//	m_pTarget = nullptr;
//
//	OBJECTTYPE m_eEnemyType = m_eObjectType == OBJECTTYPE::MONSTER ? OBJECTTYPE::PLAYER : OBJECTTYPE::MONSTER;
//	vector<CGameObject*> vEnemy = Engine::CManagement::GetInstance()->Get_GameLogic_Objects(m_eEnemyType);
//
//	_vec3  vPos, vTargetPos;
//	_float fMinDist(1000.f);
//
//	for (CGameObject* target : vEnemy)
//	{
//		if (target == nullptr || dynamic_cast<CHuman*>(target)->Get_Dead())
//			continue;
//
//		CTransform* pTargetTransCom = target->Get_Transform();
//
//		_float fX = (*m_vTransform->Get_Pos()).x - (*pTargetTransCom->Get_Pos()).x;
//		_float fY = (*m_vTransform->Get_Pos()).y - (*pTargetTransCom->Get_Pos()).y;
//		_float fZ = (*m_vTransform->Get_Pos()).z - (*pTargetTransCom->Get_Pos()).z;
//
//		_float fDist = (fX * fX + fY * fY + fZ * fZ);
//
//		_float fMaxViewDist = m_iAttackRange * m_iAttackRange * m_iAttackRange;
//		if (fDist > fMaxViewDist) {
//			continue;
//		}
//
//		if (fMinDist > fDist){
//			fMinDist = fDist;
//			m_pTarget = target;
//		}
//	}
//
//}
//
//void CHuman::Guide(const _float& fTimeDelta)
//{
//	if (m_pTarget == nullptr || m_pTarget->Get_Dead()) {
//		//m_vPickPos = *m_vTransform->Get_Pos();
//
//		if (m_eObjectType == OBJECTTYPE::PLAYER) {
//			vector<CGameObject*> pFlag = Engine::CManagement::GetInstance()->Get_GameLogic_Objects(OBJECTTYPE::FLAGPOLE);
//
//			if (pFlag.size() != 0) {
//				m_vPickPos = *pFlag.front()->Get_Transform()->Get_Pos();
//			}
//			else {
//				m_vPickPos = *m_vTransform->Get_Pos();
//			}
//		}
//		return;
//	}
//
//	CTransform* pTargetTransCom = dynamic_cast<CTransform*>(
//		m_pTarget->Get_Transform());
//	NULL_CHECK_RETURN(pTargetTransCom, );
//
//	_vec3	vTargetPos;
//	pTargetTransCom->Get_Info(INFO_POS, &vTargetPos);
//
//	m_vPickPos = vTargetPos;
//	
//}
//
//void CHuman::Pushed(CCollider* _pOther, const _float& fSpeed)
//{
//	_vec3	vOtherPos = _pOther->GetCenterPos();
//	_float* fOtherAxis = _pOther->GetAxisLen();
//
//	_vec3	vThisPos = m_pCollider->GetCenterPos();
//	_float* fThisAxis = m_pCollider->GetAxisLen();
//
//
//	// OBJECTTAG?�� ?���? ?��?�� 처리 �??��?��
//	_float fWidth = fabs(vOtherPos.x - vThisPos.x);
//	_float fHeight = fabs(vOtherPos.y - vThisPos.y);
//	_float fDepth = fabs(vOtherPos.z - vThisPos.z);
//
//	_float fRadiusX = (fOtherAxis[0] + fThisAxis[0]) - fWidth;
//	_float fRadiusY = (fOtherAxis[1] + fThisAxis[1]) - fHeight;
//	_float fRadiusZ = (fOtherAxis[2] + fThisAxis[2]) - fDepth;
//
//	_float fMinAxis = min(min(fRadiusX, fRadiusY), fRadiusZ);	// �??�� ?��??? 값이 �??�� ?���? 충돌?�� �?. ?�� 축을 �??��?��?�� ?��.
//
//	_float fDeltaTime = 1.f;
//
//	_vec3 force;
//
//	if (fRadiusY == fMinAxis)
//	{
//		if (vOtherPos.y < vThisPos.y)
//		{
//			force = { 0.f, fRadiusY, 0.f };
//		}
//		else
//		{
//			force = { 0.f, -fRadiusY, 0.f };
//		}
//
//	}
//	else if (fRadiusZ == fMinAxis)
//	{
//		if (vOtherPos.z < vThisPos.z)
//		{
//			force = { 0.f, 0.f, fRadiusZ };
//		}
//		else
//		{
//			force = { 0.f, 0.f, -fRadiusZ };
//		}
//
//	}
//	else //(fRadiusX == fMinAxis)
//	{
//
//		if (vOtherPos.x < vThisPos.x)
//		{
//			force = { fRadiusX, 0.f, 0.f };
//		}
//		else
//		{
//			force = { -fRadiusX, 0.f, 0.f };
//		}
//
//	}
//
//	if (m_pRigidBody)
//	{
//		m_pRigidBody->Add_Force(force * fSpeed);
//	}
//	else
//	{
//		m_vTransform->Move_Pos(&force, fDeltaTime, fSpeed);
//	}
//}
//
//void CHuman::Ready_Dead()
//{
//	if (m_iHP <= 0) {
//		Set_Dead();
//	}
//}

