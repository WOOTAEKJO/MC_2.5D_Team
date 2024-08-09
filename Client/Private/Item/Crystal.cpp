#include "stdafx.h"
#include "..\Header\Crystal.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "SaveLoadMgr.h"
#include "EventMgr.h"

#include "CrystalHPUI.h"

CCrystal::CCrystal(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCubeItem(pGraphicDev)
{
}

CCrystal::CCrystal(const CCrystal& rhs)
	: CCubeItem(rhs)
{
}

CCrystal::~CCrystal()
{
}

HRESULT CCrystal::Ready_GameObject()
{
	//FAILED_CHECK_RETURN(CCubeItem::Default_Component(*CSaveLoadMgr::GetInstance()->Get_ItemPartsInfoData(L"CRYSTAL")), E_FAIL);
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"CRYSTAL2"), E_FAIL);
	FAILED_CHECK_RETURN(CCrystal::Add_Component(), E_FAIL);
	CCubeItem::Ready_GameObject();

	//m_vTransform->Set_Scale(1.f, 1.f, 1.f);
	_vec3 vScale = (*m_vTransform->Get_Scale()) * 7.f;
	m_pCollider->InitOBB(m_vTransform->m_vInfo[INFO_POS], &m_vTransform->m_vInfo[INFO_RIGHT], vScale);

	m_iHP = 70.f;
	m_iMaxHP = m_iHP;
	return S_OK;
}

_int CCrystal::Update_GameObject(const _float& fTimeDelta)
{
	if (m_pUI == nullptr) {
		Create_UI();
	}

	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CCrystal::LateUpdate_GameObject()
{
	CCubeItem::LateUpdate_GameObject();
}

void CCrystal::Render_GameObject()
{
	m_pCollider->Render_Collider();

	if (m_pUI != nullptr) {
		static_cast<CUI*>(m_pUI)->Set_HideCheck(false);
	}

	CCubeItem::Render_GameObject();
}

void CCrystal::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->Get_Owner()->Get_ObjectType() == OBJECTTYPE::PLAYER) {
		//Pushed(_pOther, 0.f);
	}
}


void CCrystal::Init_Pos(const _vec3& vPos)
{
	m_vTransform->Set_Pos(vPos);
}

void CCrystal::Create_UI()
{
	//_vec3 vPos = *m_vTransform->Get_Pos(); //{ 0.f,0.f,0.f };
	//_vec3 vScale = { 200.f,15.f,1.f };

	//_matrix* matWorld = m_vTransform->Get_WorldMatrix();

	//m_pUI = CObjCreationMgr::GetInstance()->Create_UI<CCrystalHPUI>(OBJECTTYPE::UI, vPos, vScale);
	
	m_pUI = CCrystalHPUI::Create(m_pGraphicDev);
	static_cast<CCrystalHPUI*>(m_pUI)->Set_Target(this);
	Engine::CManagement::GetInstance()->Add_UI_Object(OBJECTTYPE::UI, m_pUI);


}


HRESULT CCrystal::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pRigidBody = dynamic_cast<CRigidBody*>(Engine::Clone_Proto(L"Proto_RigidBody"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_RigidBody", pComponent });

	pComponent = m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });

	/*pComponent = m_pRigidBody = dynamic_cast<CRigidBody*>(Engine::Clone_Proto(L"Proto_RigidBody"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_RigidBody", pComponent });*/

	for (int i = 0; i < ID_END; ++i)
		for (auto& iter : m_mapComponent[i])
			iter.second->Init_Component(this);

	return S_OK;
}

CCrystal* CCrystal::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCrystal* pInstance = new CCrystal(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Generator Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCrystal::Free()
{
	/*for_each(m_vecMonsterInfo.begin(), m_vecMonsterInfo.end(), CDeleteObj2());
	m_vecMonsterInfo.clear();*/
	if (m_pUI != nullptr) {
		m_pUI->Set_Dead();
	}

	CCubeItem::Free();
}
