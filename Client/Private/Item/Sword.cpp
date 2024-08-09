#include "stdafx.h"
#include "..\Header\Sword.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CSword::CSword(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCubeItem(pGraphicDev)
{
}

CSword::CSword(const CSword& rhs)
	: CCubeItem(rhs)
{
}

CSword::~CSword()
{
}

HRESULT CSword::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}

CSword* CSword::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType)
{
	CSword* pInstance = new CSword(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject(pObj, eParts, eWeaponType))) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSword::Free()
{

	CCubeItem::Free();
}


HRESULT CSword::Ready_GameObject(CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"SWORD"), E_FAIL);
	
	NULL_CHECK_RETURN(pObj, E_FAIL);
	m_Owner = pObj;
	m_OwnerParts = eParts;

	m_vTransform->Set_ParentsWorldMatrix(static_cast<CHuman*>(m_Owner)->Get_Parts_Transform()[m_OwnerParts]->Get_WorldMatrix());

	//CCubeItem::Ready_GameObject();

	m_iHP = 100.f;

	return S_OK;
}

_int CSword::Update_GameObject(const _float& fTimeDelta)
{
	if (m_Owner==nullptr || m_Owner->Get_Dead()) {
		Set_Dead();
		return 0;
	}

	m_vTransform->Set_ParentsWorldMatrix(static_cast<CHuman*>(m_Owner)->Get_Parts_Transform()[m_OwnerParts]->Get_WorldMatrix());

	return CCubeItem::Update_GameObject(fTimeDelta);

	
}

void CSword::LateUpdate_GameObject()
{
	CCubeItem::LateUpdate_GameObject();
}

void CSword::Render_GameObject()
{
	CCubeItem::Render_GameObject();
}
