#include "stdafx.h"
#include "..\Header\FourthFlagAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CFourthFlagAttack::CFourthFlagAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	:CFlagpole(pGraphicDev)
{
}

CFourthFlagAttack::CFourthFlagAttack(const CFourthFlagAttack& rhs)
	: CFlagpole(rhs)
{
}

CFourthFlagAttack::~CFourthFlagAttack()
{
}

HRESULT CFourthFlagAttack::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}

CFourthFlagAttack* CFourthFlagAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFourthFlagAttack* pInstance = new CFourthFlagAttack(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFourthFlagAttack::Free()
{
	CFlagpole::Free();
}


HRESULT CFourthFlagAttack::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"FOURTHFLAGATK"), E_FAIL);
	CFlagpole::Ready_GameObject();
	m_iHP = 10000.f;
	m_vTransform->m_vAngle.y = D3DXToRadian(90.f);
	return S_OK;
}

_int CFourthFlagAttack::Update_GameObject(const _float& fTimeDelta)
{


	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CFourthFlagAttack::LateUpdate_GameObject()
{
	CFlagpole::LateUpdate_GameObject();
}

void CFourthFlagAttack::Render_GameObject()
{
	CFlagpole::Render_GameObject();
}

