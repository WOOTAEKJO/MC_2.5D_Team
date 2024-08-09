#include "stdafx.h"
#include "..\Header\FirstFlagAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CFirstFlagAttack::CFirstFlagAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	:CFlagpole(pGraphicDev)
{
}

CFirstFlagAttack::CFirstFlagAttack(const CFirstFlagAttack& rhs)
	: CFlagpole(rhs)
{
}

CFirstFlagAttack::~CFirstFlagAttack()
{
}

HRESULT CFirstFlagAttack::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}

CFirstFlagAttack* CFirstFlagAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFirstFlagAttack* pInstance = new CFirstFlagAttack(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFirstFlagAttack::Free()
{
	CFlagpole::Free();
}


HRESULT CFirstFlagAttack::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"FIRSTFLAGATK"), E_FAIL);
	CFlagpole::Ready_GameObject();
	m_iHP = 10000.f;
	m_vTransform->m_vAngle.y = D3DXToRadian(90.f);
	return S_OK;
}

_int CFirstFlagAttack::Update_GameObject(const _float& fTimeDelta)
{


	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CFirstFlagAttack::LateUpdate_GameObject()
{
	CFlagpole::LateUpdate_GameObject();
}

void CFirstFlagAttack::Render_GameObject()
{
	CFlagpole::Render_GameObject();
}

