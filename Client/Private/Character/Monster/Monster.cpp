#include "stdafx.h"
#include "..\Header\Monster.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "BlockMap.h"
#include "CubeItem.h"
#include "SaveLoadMgr.h"
#include "AStarMgr.h"

#include "TestBullet.h"

#include "Sword.h"
#include "Bow.h"
#include "Arrow.h"

#include "ResourceMgr.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
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

CMonster::CMonster(const CMonster& rhs)
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

CMonster::~CMonster()
{
}

HRESULT CMonster::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CMonster::Default_Ratio(), E_FAIL);
	//FAILED_CHECK_RETURN(CMonster::Ready_GameObject(), E_FAIL);
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_vTransform->m_vInfo[INFO_POS].y += 1.f;
	m_vTransform->Set_Scale(3.f, 3.7f, 1.5f);
	m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], *m_vTransform->Get_Scale());

	return S_OK;
}

_int CMonster::Update_GameObject(const _float& fTimeDelta)
{
	if (m_bDead)
	{
		CResourceMgr::GetInstance()->Drop_Emerald(m_iCost, *m_vTransform->Get_Pos());
		return S_OK;
	}

	Check_Range_Of_View();

	if (m_pVecFrame->size() != 0) {

		m_pTransformCom[(_uint)MONSTERPARTS::HEAD]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::HEAD].eETC_Par]->m_matWorld;
		m_pTransformCom[(_uint)MONSTERPARTS::BODY]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::BODY].eETC_Par]->m_matWorld;
		m_pTransformCom[(_uint)MONSTERPARTS::LEFT_ARM]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::LEFT_ARM].eETC_Par]->m_matWorld;
		m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_ARM]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::RIGHT_ARM].eETC_Par]->m_matWorld;
		m_pTransformCom[(_uint)MONSTERPARTS::LEFT_LEG]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::LEFT_LEG].eETC_Par]->m_matWorld;
		m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_LEG]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::RIGHT_LEG].eETC_Par]->m_matWorld;

		m_pTransformCom[(_uint)MONSTERPARTS::ETC1]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::ETC1].eETC_Par]->m_matWorld;
		m_pTransformCom[(_uint)MONSTERPARTS::ETC2]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::ETC2].eETC_Par]->m_matWorld;
		m_pTransformCom[(_uint)MONSTERPARTS::ETC3]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::ETC3].eETC_Par]->m_matWorld;
		m_pTransformCom[(_uint)MONSTERPARTS::ETC4]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::ETC4].eETC_Par]->m_matWorld;
		m_pTransformCom[(_uint)MONSTERPARTS::ETC5]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::ETC5].eETC_Par]->m_matWorld;
		m_pTransformCom[(_uint)MONSTERPARTS::ETC6]->m_matParWorld = m_pTransformCom[(_uint)(*m_pVecFrame)[0][(_uint)MONSTERPARTS::ETC6].eETC_Par]->m_matWorld;
	}
	
	
	/*m_pTransformCom[(_uint)MONSTERPARTS::HEAD]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;
	m_pTransformCom[(_uint)MONSTERPARTS::BODY]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;
	m_pTransformCom[(_uint)MONSTERPARTS::LEFT_ARM]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;
	m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_ARM]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;
	m_pTransformCom[(_uint)MONSTERPARTS::LEFT_LEG]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;
	m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_LEG]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;

	m_pTransformCom[(_uint)MONSTERPARTS::ETC1]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC2]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC3]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC4]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC5]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC6]->m_matParWorld = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_matWorld;*/

	_vec3 vPos;
	vPos = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_vInfo[INFO_POS];

	if (m_eObjectType != OBJECTTYPE::MONSTER_DEMO) {
		//_float fHeight = dynamic_cast<CBlockMap*>(Engine::CManagement::GetInstance()->Get_Environment_Objects(OBJECTTYPE::BLOCKMAP).front())->
		//	Get_ClosestBelowBlockHeight(vPos.x, vPos.y, vPos.z);

		//if (fHeight > 0)
		//	m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_vInfo[INFO_POS].y = fHeight + 3.4f;

		m_pTransformCom[TOTAL]->m_vInfo[INFO_POS].y = 3.4f;
	}

	m_pRigidBody->Update_RigidBody(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 	CCharacter::Update_GameObject(fTimeDelta);
}

void CMonster::LateUpdate_GameObject()
{
	//Height_On_Terrain(true);

	CCharacter::LateUpdate_GameObject();
}

void CMonster::Render_GameObject()
{
	/*D3DMATERIAL9			tMtrl;
	ZeroMemory(&tMtrl, sizeof(D3DMATERIAL9));

	tMtrl.Diffuse = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Specular = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Ambient = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Emissive = { 0.f, 0.f, 0.f, 0.f };
	tMtrl.Power = 0.f;

	m_pGraphicDev->SetMaterial(&tMtrl);*/

	for (_ushort i = (_uint)MONSTERPARTS::HEAD; i < (_uint)MONSTERPARTS::ETC1; ++i)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom[i]->Get_WorldMatrix());
		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		m_pTextureCom[i]->Render_Textrue(m_iTex_Num);
		m_pBufferCom[i]->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}

	for (_ushort i = (_uint)MONSTERETCPARTS::ETC1; i < (_uint)MONSTERETCPARTS::MONSTERETCPARTS_END; ++i)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom[i+7]->Get_WorldMatrix());
		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		m_pTextureCom[i+7]->Render_Textrue(m_iTex_Num);
		m_pETCBufferCom[i]->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}

	if (m_eObjectType != OBJECTTYPE::MONSTER_DEMO) {
		m_pCollider->Render_Collider();
	}
	CCharacter::Render_GameObject();
}


HRESULT CMonster::SetUp_Parts(const _tchar* Head,
	const _tchar* Body,
	const _tchar* Arm1,
	const _tchar* Arm2,
	const _tchar* Leg1,
	const _tchar* Leg2,
	const _tchar* ETC1,
	const _tchar* ETC2,
	const _tchar* ETC3,
	const _tchar* ETC4,
	const _tchar* ETC5,
	const _tchar* ETC6)
{
	CComponent* pComponent = nullptr;

	// ��ü
	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::TOTAL] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_TOTAL", pComponent });

	pComponent = m_pCalculatorCom[(_uint)MONSTERPARTS::TOTAL] = dynamic_cast<CCalculator*>(Engine::Clone_Proto(L"Proto_Calculator"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Calculator_TOTAL", pComponent });

	//�Ӹ�
	pComponent = m_pBufferCom[(_uint)MONSTERPARTS::HEAD] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_HEAD", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::HEAD] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_HEAD", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::HEAD] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Head));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_HEAD", pComponent });

	//����

	pComponent = m_pBufferCom[(_uint)MONSTERPARTS::BODY] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_BODY", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::BODY] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_BODY", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::BODY] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Body));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_BODY", pComponent });

	// ����
	pComponent = m_pBufferCom[(_uint)MONSTERPARTS::LEFT_ARM] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_LEFT_ARM", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::LEFT_ARM] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_LEFT_ARM", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::LEFT_ARM] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Arm1));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_LEFT_ARM", pComponent });


	// ������
	pComponent = m_pBufferCom[(_uint)MONSTERPARTS::RIGHT_ARM] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_RIGHT_ARM", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_ARM] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_RIGHT_ARM", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::RIGHT_ARM] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Arm2));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_RIGHT_ARM", pComponent });


	// �޴ٸ�
	pComponent = m_pBufferCom[(_uint)MONSTERPARTS::LEFT_LEG] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_LEFT_LEG", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::LEFT_LEG] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_LEFT_LEG", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::LEFT_LEG] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Leg1));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_LEFT_LEG", pComponent });


	// �����ٸ�
	pComponent = m_pBufferCom[(_uint)MONSTERPARTS::RIGHT_LEG] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_RIGHT_LEG", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_LEG] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_RIGHT_LEG", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::RIGHT_LEG] = dynamic_cast<CTexture*>(Engine::Clone_Proto(Leg2));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_RIGHT_LEG", pComponent });

	//// ETC1
	//pComponent = m_pBufferCom[(_uint)MONSTERPARTS::ETC1] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_RIGHT_ETC1", pComponent });

	//pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC1] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC1", pComponent });

	//pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC1] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC1));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC1", pComponent });

	//// ETC2
	//pComponent = m_pBufferCom[(_uint)MONSTERPARTS::ETC2] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_RIGHT_ETC2", pComponent });

	//pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC2] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC2", pComponent });

	//pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC2] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC2));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC2", pComponent });

	//// ETC3
	//pComponent = m_pBufferCom[(_uint)MONSTERPARTS::ETC3] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_RIGHT_ETC3", pComponent });

	//pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC3] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC3", pComponent });

	//pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC3] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC3));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC3", pComponent });

	//// ETC4
	//pComponent = m_pBufferCom[(_uint)MONSTERPARTS::ETC4] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_RIGHT_ETC4", pComponent });

	//pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC4] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC4", pComponent });

	//pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC4] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC4));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC4", pComponent });

	//// ETC5
	//pComponent = m_pBufferCom[(_uint)MONSTERPARTS::ETC5] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_RIGHT_ETC5", pComponent });

	//pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC5] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC5", pComponent });

	//pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC5] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC5));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC5", pComponent });

	//// ETC6
	//pComponent = m_pBufferCom[(_uint)MONSTERPARTS::ETC6] = dynamic_cast<CCubeTexTop*>(Engine::Clone_Proto(L"Proto_CubeTexTop"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_RIGHT_ETC6", pComponent });

	//pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC6] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC6", pComponent });

	//pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC6] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC6));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC6", pComponent });

	// ETC1
	pComponent = m_pETCBufferCom[(_uint)MONSTERETCPARTS::ETC1] = dynamic_cast<CBlockTex*>(Engine::Clone_Proto(L"Proto_BlockTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_ETC1", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC1] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC1", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC1] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC1));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC1", pComponent });

	// ETC2
	pComponent = m_pETCBufferCom[(_uint)MONSTERETCPARTS::ETC2] = dynamic_cast<CBlockTex*>(Engine::Clone_Proto(L"Proto_BlockTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_ETC2", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC2] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC2", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC2] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC2));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC2", pComponent });

	// ETC3
	pComponent = m_pETCBufferCom[(_uint)MONSTERETCPARTS::ETC3] = dynamic_cast<CBlockTex*>(Engine::Clone_Proto(L"Proto_BlockTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_ETC3", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC3] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC3", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC3] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC3));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC3", pComponent });

	// ETC4
	pComponent = m_pETCBufferCom[(_uint)MONSTERETCPARTS::ETC4] = dynamic_cast<CBlockTex*>(Engine::Clone_Proto(L"Proto_BlockTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_ETC4", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC4] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC4", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC4] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC4));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC4", pComponent });

	// ETC5
	pComponent = m_pETCBufferCom[(_uint)MONSTERETCPARTS::ETC5] = dynamic_cast<CBlockTex*>(Engine::Clone_Proto(L"Proto_BlockTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_ETC5", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC5] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC5", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC5] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC5));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC5", pComponent });

	// ETC6
	pComponent = m_pETCBufferCom[(_uint)MONSTERETCPARTS::ETC6] = dynamic_cast<CBlockTex*>(Engine::Clone_Proto(L"Proto_BlockTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_ETC6", pComponent });

	pComponent = m_pTransformCom[(_uint)MONSTERPARTS::ETC6] = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_ETC6", pComponent });

	pComponent = m_pTextureCom[(_uint)MONSTERPARTS::ETC6] = dynamic_cast<CTexture*>(Engine::Clone_Proto(ETC6));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_ETC6", pComponent });

	// 공용
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

HRESULT CMonster::Default_Ratio()
{
	m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_vScale.x *= 1 / 2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_vScale.y *= 1 / 2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->m_vScale.z *= 1 / 2.f;

	m_pTransformCom[(_uint)MONSTERPARTS::HEAD]->m_vScale.x *= 8 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::HEAD]->m_vScale.y *= 8 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::HEAD]->m_vScale.z *= 8 / 10.f;

	m_pTransformCom[(_uint)MONSTERPARTS::BODY]->m_vScale.x *= 8 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::BODY]->m_vScale.y *= 12 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::BODY]->m_vScale.z *= 4 / 10.f;

	m_pTransformCom[(_uint)MONSTERPARTS::LEFT_ARM]->m_vScale.x *= 4 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::LEFT_ARM]->m_vScale.y *= 12 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::LEFT_ARM]->m_vScale.z *= 4 / 10.f;

	m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_ARM]->m_vScale.x *= 4 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_ARM]->m_vScale.y *= 12 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_ARM]->m_vScale.z *= 4 / 10.f;

	m_pTransformCom[(_uint)MONSTERPARTS::LEFT_LEG]->m_vScale.x *= 4 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::LEFT_LEG]->m_vScale.y *= 12 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::LEFT_LEG]->m_vScale.z *= 4 / 10.f;

	m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_LEG]->m_vScale.x *= 4 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_LEG]->m_vScale.y *= 12 / 10.f;
	m_pTransformCom[(_uint)MONSTERPARTS::RIGHT_LEG]->m_vScale.z *= 4 / 10.f;

	m_pTransformCom[(_uint)MONSTERPARTS::ETC1]->m_vScale.x *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC1]->m_vScale.y *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC1]->m_vScale.z *= 1/2.f;
															  
	m_pTransformCom[(_uint)MONSTERPARTS::ETC2]->m_vScale.x *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC2]->m_vScale.y *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC2]->m_vScale.z *= 1/2.f;
															  
	m_pTransformCom[(_uint)MONSTERPARTS::ETC3]->m_vScale.x *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC3]->m_vScale.y *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC3]->m_vScale.z *= 1/2.f;
															  
	m_pTransformCom[(_uint)MONSTERPARTS::ETC4]->m_vScale.x *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC4]->m_vScale.y *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC4]->m_vScale.z *= 1/2.f;
															  
	m_pTransformCom[(_uint)MONSTERPARTS::ETC5]->m_vScale.x *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC5]->m_vScale.y *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC5]->m_vScale.z *= 1/2.f;
															  
	m_pTransformCom[(_uint)MONSTERPARTS::ETC6]->m_vScale.x *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC6]->m_vScale.y *= 1/2.f;
	m_pTransformCom[(_uint)MONSTERPARTS::ETC6]->m_vScale.z *= 1/2.f;

	//Set_VecFrame(CSaveLoadMgr::GetInstance()->Get_AnimationData(L"HUMANIDLE"));

	return S_OK;
}

void CMonster::ETC_Control(const _int& iIndex, vector<MONSTERFRAME*>& vecFrame)
{
	if (!m_bETCControl) {
		Get_Parts_Transform()[(_uint)MONSTERPARTS::HEAD]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::HEAD].vRotation));

		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC1]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC1].vPosition);
		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC2]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC2].vPosition);
		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC3]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC3].vPosition);
		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC4]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC4].vPosition);
		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC5]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC5].vPosition);
		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC6]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC6].vPosition);

		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC1]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC1].vRotation));
		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC2]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC2].vRotation));
		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC3]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC3].vRotation));
		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC4]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC4].vRotation));
		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC5]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC5].vRotation));
		Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC6]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC6].vRotation));
	}
}



void CMonster::Animation_Frame(const float& fTimeDelta)
{
	if (nullptr == m_pVecFrame) return;

	if (m_fTotalFrameCount > (60.f / 1.f)) {
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

void CMonster::Update_Matrix(const _int& iIndex, vector<MONSTERFRAME*>& vecFrame)
{

	Animation_Total_Frame_Setting(iIndex, vecFrame);

	Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->m_vInfo[INFO_POS].y = vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vPosition.y;

	//Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->m_vAngle = D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vRotation);
	//Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vInfo[INFO_POS] = vecFrame[iIndex][(_uint)PARTS::TOTAL].vPosition;
	//Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->m_vInfo[INFO_POS].x = vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vPosition.x;
	//Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->m_vInfo[INFO_POS].y = vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vPosition.y;
	//Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->m_vInfo[INFO_POS].z = vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vPosition.z;
	Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vScale);

	
	Get_Parts_Transform()[(_uint)MONSTERPARTS::HEAD]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::HEAD].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::HEAD]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::HEAD].vScale);

	Get_Parts_Transform()[(_uint)MONSTERPARTS::BODY]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::BODY].vRotation));
	Get_Parts_Transform()[(_uint)MONSTERPARTS::BODY]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::BODY].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::BODY]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::BODY].vScale);

	Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_ARM]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_ARM].vRotation));
	Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_ARM]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_ARM].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_ARM]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_ARM].vScale);

	Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_ARM]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_ARM].vRotation));
	Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_ARM]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_ARM].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_ARM]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_ARM].vScale);

	Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_LEG]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_LEG].vRotation));
	Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_LEG]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_LEG].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::LEFT_LEG]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::LEFT_LEG].vScale);

	Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_LEG]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_LEG].vRotation));
	Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_LEG]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_LEG].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::RIGHT_LEG]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::RIGHT_LEG].vScale);

	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC1]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC1].vRotation));
	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC1]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC1].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC1]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC1].vScale);

	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC2]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC2].vRotation));
	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC2]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC2].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC2]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC2].vScale);

	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC3]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC3].vRotation));
	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC3]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC3].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC3]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC3].vScale);

	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC4]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC4].vRotation));
	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC4]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC4].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC4]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC4].vScale);

	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC5]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC5].vRotation));
	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC5]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC5].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC5]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC5].vScale);

	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC6]->Set_Angle(D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC6].vRotation));
	//Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC6]->Set_Pos(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC6].vPosition);
	Get_Parts_Transform()[(_uint)MONSTERPARTS::ETC6]->Set_Scale(vecFrame[iIndex][(_uint)MONSTERPARTS::ETC6].vScale);

	ETC_Control(iIndex, vecFrame);
}

void CMonster::Animation_Total_Frame_Setting(const _int& iIndex, vector<MONSTERFRAME*>& vecFrame)
{
	if (m_bIsRotate == false) {
		//m_InitTotPos = *m_pTransformCom[TOTAL]->Get_Pos();
		m_InitTotRot = *m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->Get_Angle();
		// 초기 값을 저장.

	}
	else {
		//m_pTransformCom[TOTAL]->Set_Pos(m_InitTotPos);
		m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->Set_Angle(m_InitTotRot);

		//Get_Parts_Transform()[(_uint)PARTS::TOTAL]->m_vInfo[INFO_POS].y = vecFrame[iIndex][(_uint)PARTS::TOTAL].vPosition.y;
		Get_Parts_Transform()[(_uint)MONSTERPARTS::TOTAL]->m_vAngle +=
			D3DXToRadian(vecFrame[iIndex][(_uint)MONSTERPARTS::TOTAL].vRotation);

	}

}

bool CMonster::Is_Animation_Frame_End()
{
	return m_FrameCount > (m_pVecFrame->size() - 1);
}

_bool CMonster::Attack_Stance(const _float& fRange)
{
	if (Is_Target_Dead()) {
		return false;
	}

	CTransform* pTargetTransCom = (m_pTarget)->Get_Transform();
	if (pTargetTransCom == nullptr || pTargetTransCom->Get_Owner() == nullptr || pTargetTransCom->Get_Owner()->Get_Dead()) 
	{
		return false;
	}

	_vec3 vDist, vPos, vTargetPos;
	//_float fRadius = 2.7f;

	m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->Get_Info(INFO_POS, &vPos);
	pTargetTransCom->Get_Info(INFO_POS, &vTargetPos);

	vDist = vPos - vTargetPos;

	_float fX = vDist.x;
	_float fY = vDist.y;
	_float fZ = vDist.z;



	if ((fX * fX + fY * fY + fZ * fZ) <= fRange * fRange) {
		return true;
	}

	return false;
}

void CMonster::Free()
{
	CResourceMgr::GetInstance()->Add_Money(m_iCost);
	//CResourceMgr::GetInstance()->Drop_Emerald(m_iCost, *m_vTransform->Get_Pos());
	CCharacter::Free();
}

//void CMonster::Delete_Weapon()
//{
//	if (m_pWeapon != nullptr) {
//		m_pWeapon->Set_Dead();
//	}
//}
//
//void CMonster::Delete_SubWeapon()
//{
//	if (m_pSubWeapon != nullptr)
//		m_pSubWeapon->Set_Dead();
//}
//
//HRESULT CMonster::Add_SubWeapon(WEAPONTYPE eWeaponType)
//{
//	CCubeItem* pGameObject = nullptr;
//
//	if (m_eWeaponType == WEAPONTYPE::BOW) {
//		pGameObject = CArrow::Create(m_pGraphicDev, this, RIGHT_ARM);
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

//HRESULT CMonster::Add_Weapon(WEAPONTYPE eWeaponType)
//{
//	CCubeItem* pGameObject = nullptr;
//	/*if (eWeaponType == WEAPONTYPE::SWORD) {
//		pGameObject = CSword::Create(m_pGraphicDev, this, RIGHT_ARM);
//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	}
//	if (eWeaponType == WEAPONTYPE::BOW) {
//		pGameObject = CBow::Create(m_pGraphicDev, this, LEFT_ARM);
//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	}*/
//
//	m_pWeapon = pGameObject;
//	CManagement::GetInstance()->Add_GameLogic_Object(OBJECTTYPE::WEAPON, pGameObject);
//	m_eWeaponType = eWeaponType;
//
//	return S_OK;
//}
//
//void CMonster::Create_Bullet()
//{
//	{
//		CGameObject* gameObject = CTestBullet::Create(m_pGraphicDev);
//		gameObject->Get_Transform()->m_vInfo[INFO_LOOK] = m_vTransform->m_vInfo[INFO_LOOK];
//		gameObject->Get_Transform()->m_vInfo[INFO_POS] = m_vTransform->m_vInfo[INFO_POS];
//
//		Engine::CManagement::GetInstance()->Add_GameLogic_Object(OBJECTTYPE::ALLY_BULLET, gameObject);
//	};
//}
//
//_vec3 CMonster::Picking_On_Terrain()
//{
//	//BlockMap
//	_vec3 vecIntersect(0.f, 0.f, 0.f);
//	const list<CBlock*>* pBlockList = dynamic_cast<CBlockMap*>(
//		Engine::CManagement::GetInstance()
//		->Get_Environment_Objects(OBJECTTYPE::BLOCKMAP).front())
//		->Get_BlockListPtr();
//
//	for (auto& pBlock : *pBlockList) {
//		vecIntersect = m_pCalculatorCom[(_uint)MONSTERPARTS::TOTAL]->Picking_OnBlockTop(g_hWnd, pBlock->Get_Pos());
//		if (_vec3(0.f, 0.f, 0.f) != vecIntersect)
//			return vecIntersect;
//	}
//
//	return  _vec3(0.f, 0.f, 0.f);
//}
//
//void CMonster::Set_Destination()
//{
//	_vec3 vBuf(0.f, 0.f, 0.f), vZero(0.f, 0.f, 0.f);
//
//	vBuf = Picking_On_Terrain();
//
//	if (vBuf != vZero)
//		m_vPickPos = vBuf;
//}
//
//_vec3 CMonster::Calc_Distance_To_Destination()
//{
//	return m_vPickPos - m_vTransform->m_vInfo[INFO_POS];
//}
//
//bool CMonster::Is_Arrived()
//{
//	_vec3 distance = Calc_Distance_To_Destination();
//	return !(abs(distance.x) + abs(distance.y) + abs(distance.z) > 2.7f);
//}
//
//void CMonster::Move(const _float& fTimeDelta, const _float& fSpeed)
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
//
//void CMonster::Target_Dir_Update()
//{
//	if (m_pTarget == nullptr || m_pTarget->Get_Dead())
//		return;
//
//	m_pTarget->Get_Transform()->Get_Info(INFO_POS, &m_vPickPos);
//}



//void CMonster::Create_ATTColl(const _float& fDeadTime, const _vec3& vScale, const _float& fDist, OBJECTTYPE eObjType, CGameObject* pOwner)
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
//void CMonster::LookAt_Target()
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
//		if (target == nullptr || dynamic_cast<CMonster*>(target)->Get_Dead())
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
//		if (fMinDist > fDist) {
//			fMinDist = fDist;
//			m_pTarget = target;
//		}
//	}
//
//}
//
//void CMonster::Guide(const _float& fTimeDelta)
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
//void CMonster::Pushed(CCollider* _pOther, const _float& fSpeed)
//{
//	_vec3	vOtherPos = _pOther->GetCenterPos();
//	_float* fOtherAxis = _pOther->GetAxisLen();
//
//	_vec3	vThisPos = m_pCollider->GetCenterPos();
//	_float* fThisAxis = m_pCollider->GetAxisLen();
//
//
//	// OBJECTTAG에 따른 예외 처리 가능성
//	_float fWidth = fabs(vOtherPos.x - vThisPos.x);
//	_float fHeight = fabs(vOtherPos.y - vThisPos.y);
//	_float fDepth = fabs(vOtherPos.z - vThisPos.z);
//
//	_float fRadiusX = (fOtherAxis[0] + fThisAxis[0]) - fWidth;
//	_float fRadiusY = (fOtherAxis[1] + fThisAxis[1]) - fHeight;
//	_float fRadiusZ = (fOtherAxis[2] + fThisAxis[2]) - fDepth;
//
//	_float fMinAxis = min(min(fRadiusX, fRadiusY), fRadiusZ);	// 가장 작은 값이 가장 얕게 충돌한 축. 이 축을 밀어내야 함.
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
//void CMonster::Ready_Dead()
//{
//	if (m_iHP <= 0) {
//		Set_Dead();
//	}
//}


