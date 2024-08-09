#include "stdafx.h"
#include "..\Header\SecondFlagAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CSecondFlagAttack::CSecondFlagAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	:CFlagpole(pGraphicDev)
{
}

CSecondFlagAttack::CSecondFlagAttack(const CSecondFlagAttack& rhs)
	: CFlagpole(rhs)
{
}

CSecondFlagAttack::~CSecondFlagAttack()
{
}

HRESULT CSecondFlagAttack::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}

CSecondFlagAttack* CSecondFlagAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSecondFlagAttack* pInstance = new CSecondFlagAttack(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSecondFlagAttack::Free()
{
	CFlagpole::Free();
}


HRESULT CSecondFlagAttack::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"SECONDFLAGATK"), E_FAIL);
	CFlagpole::Ready_GameObject();
	m_iHP = 10000.f;
	m_vTransform->m_vAngle.y = D3DXToRadian(90.f);
	return S_OK;
}

_int CSecondFlagAttack::Update_GameObject(const _float& fTimeDelta)
{


	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CSecondFlagAttack::LateUpdate_GameObject()
{
	CFlagpole::LateUpdate_GameObject();
}

void CSecondFlagAttack::Render_GameObject()
{
	CFlagpole::Render_GameObject();
}

