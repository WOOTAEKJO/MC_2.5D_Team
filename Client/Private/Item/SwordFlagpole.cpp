#include "stdafx.h"
#include "..\Header\SwordFlagpole.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CSwordFlagpole::CSwordFlagpole(LPDIRECT3DDEVICE9 pGraphicDev)
	:CFlagpole(pGraphicDev)
{
}

CSwordFlagpole::CSwordFlagpole(const CSwordFlagpole& rhs)
	: CFlagpole(rhs)
{
}

CSwordFlagpole::~CSwordFlagpole()
{
}

HRESULT CSwordFlagpole::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}

CSwordFlagpole* CSwordFlagpole::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSwordFlagpole* pInstance = new CSwordFlagpole(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSwordFlagpole::Free()
{
	CFlagpole::Free();
}


HRESULT CSwordFlagpole::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"FOURTHFLAGEPOLE"), E_FAIL);
	CFlagpole::Ready_GameObject();
	m_iHP = 100.f;
	m_vTransform->m_vAngle.y = D3DXToRadian(90.f);
	return S_OK;
}

_int CSwordFlagpole::Update_GameObject(const _float& fTimeDelta)
{
	

	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CSwordFlagpole::LateUpdate_GameObject()
{
	CFlagpole::LateUpdate_GameObject();
}

void CSwordFlagpole::Render_GameObject()
{
	CFlagpole::Render_GameObject();
}

