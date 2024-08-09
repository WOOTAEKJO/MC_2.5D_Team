#include "stdafx.h"
#include "..\Header\Shield.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CShield::CShield(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCubeItem(pGraphicDev)
{
}

CShield::CShield(const CShield& rhs)
	: CCubeItem(rhs)
{
}

CShield::~CShield()
{
}

HRESULT CShield::Add_Component()
{
	return S_OK;
}

CShield* CShield::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType)
{
	CShield* pInstance = new CShield(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject(pObj, eParts, eWeaponType))) {
		Safe_Release(pInstance);
		MSG_BOX("Bow Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShield::Free()
{

	CCubeItem::Free();
}


HRESULT CShield::Ready_GameObject(CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"SHIELD"), E_FAIL);

	NULL_CHECK_RETURN(pObj, E_FAIL);
	m_Owner = pObj;
	m_OwnerParts = eParts;

	m_vTransform->Set_ParentsWorldMatrix(static_cast<CHuman*>(m_Owner)->Get_Parts_Transform()[m_OwnerParts]->Get_WorldMatrix());

	CCubeItem::Ready_GameObject();

	m_iHP = 100.f;

	return S_OK;
}

_int CShield::Update_GameObject(const _float& fTimeDelta)
{
	if (m_Owner == nullptr || m_Owner->Get_Dead()) {
		Set_Dead();
		return 0;
	}

	m_vTransform->Set_ParentsWorldMatrix(static_cast<CHuman*>(m_Owner)->Get_Parts_Transform()[m_OwnerParts]->Get_WorldMatrix());

	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CShield::LateUpdate_GameObject()
{
	CCubeItem::LateUpdate_GameObject();
}

void CShield::Render_GameObject()
{
	CCubeItem::Render_GameObject();
}
