#include "stdafx.h"
#include "..\Header\FirstFlagpole.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CFirstFlagpole::CFirstFlagpole(LPDIRECT3DDEVICE9 pGraphicDev)
	:CFlagpole(pGraphicDev)
{
}

CFirstFlagpole::CFirstFlagpole(const CFirstFlagpole& rhs)
	: CFlagpole(rhs)
{
}

CFirstFlagpole::~CFirstFlagpole()
{
}

HRESULT CFirstFlagpole::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}

CFirstFlagpole* CFirstFlagpole::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFirstFlagpole* pInstance = new CFirstFlagpole(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFirstFlagpole::Free()
{
	CFlagpole::Free();
}


HRESULT CFirstFlagpole::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"FIRSTFLAGMOVE"), E_FAIL);
	CFlagpole::Ready_GameObject();
	m_iHP = 10000.f;
	m_vTransform->m_vAngle.y = D3DXToRadian(90.f);
	return S_OK;
}

_int CFirstFlagpole::Update_GameObject(const _float& fTimeDelta)
{


	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CFirstFlagpole::LateUpdate_GameObject()
{
	CFlagpole::LateUpdate_GameObject();
}

void CFirstFlagpole::Render_GameObject()
{
	CFlagpole::Render_GameObject();
}

