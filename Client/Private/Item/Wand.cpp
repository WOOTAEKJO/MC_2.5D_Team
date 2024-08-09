#include "stdafx.h"
#include "..\Header\Wand.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CWand::CWand(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCubeItem(pGraphicDev)
{
}

CWand::CWand(const CWand& rhs)
	: CCubeItem(rhs)
{
}

CWand::~CWand()
{
}

HRESULT CWand::Add_Component()
{
	return S_OK;
}

CWand* CWand::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType)
{
	CWand* pInstance = new CWand(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject(pObj, eParts, eWeaponType))) {
		Safe_Release(pInstance);
		MSG_BOX("Bow Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWand::Free()
{

	CCubeItem::Free();
}


HRESULT CWand::Ready_GameObject(CGameObject* pObj, PARTS eParts, WEAPONTYPE eWeaponType)
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"WAND"), E_FAIL);

	NULL_CHECK_RETURN(pObj, E_FAIL);
	m_Owner = pObj;
	m_OwnerParts = eParts;

	m_vTransform->Set_ParentsWorldMatrix(static_cast<CHuman*>(m_Owner)->Get_Parts_Transform()[m_OwnerParts]->Get_WorldMatrix());

	CCubeItem::Ready_GameObject();

	m_iHP = 100.f;

	return S_OK;
}

_int CWand::Update_GameObject(const _float& fTimeDelta)
{
	if (m_Owner == nullptr || m_Owner->Get_Dead()) {
		Set_Dead();
		return 0;
	}

	m_vTransform->Set_ParentsWorldMatrix(static_cast<CHuman*>(m_Owner)->Get_Parts_Transform()[m_OwnerParts]->Get_WorldMatrix());

	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CWand::LateUpdate_GameObject()
{
	CCubeItem::LateUpdate_GameObject();
}

void CWand::Render_GameObject()
{
	CCubeItem::Render_GameObject();
}
