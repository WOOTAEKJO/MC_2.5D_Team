#include "stdafx.h"
#include "..\Header\FourthFlagpole.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CFourthFlagpole::CFourthFlagpole(LPDIRECT3DDEVICE9 pGraphicDev)
	:CFlagpole(pGraphicDev)
{
}

CFourthFlagpole::CFourthFlagpole(const CFourthFlagpole& rhs)
	: CFlagpole(rhs)
{
}

CFourthFlagpole::~CFourthFlagpole()
{
}

HRESULT CFourthFlagpole::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}

CFourthFlagpole* CFourthFlagpole::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFourthFlagpole* pInstance = new CFourthFlagpole(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFourthFlagpole::Free()
{
	CFlagpole::Free();
}


HRESULT CFourthFlagpole::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"FOURTHFLAGMOVE"), E_FAIL);
	CFlagpole::Ready_GameObject();
	m_iHP = 10000.f;
	m_vTransform->m_vAngle.y = D3DXToRadian(90.f);
	return S_OK;
}

_int CFourthFlagpole::Update_GameObject(const _float& fTimeDelta)
{


	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CFourthFlagpole::LateUpdate_GameObject()
{
	CFlagpole::LateUpdate_GameObject();
}

void CFourthFlagpole::Render_GameObject()
{
	CFlagpole::Render_GameObject();
}

