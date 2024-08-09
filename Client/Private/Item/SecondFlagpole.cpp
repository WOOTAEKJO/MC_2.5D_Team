#include "stdafx.h"
#include "..\Header\SecondFlagpole.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CSecondFlagpole::CSecondFlagpole(LPDIRECT3DDEVICE9 pGraphicDev)
	:CFlagpole(pGraphicDev)
{
}

CSecondFlagpole::CSecondFlagpole(const CSecondFlagpole& rhs)
	: CFlagpole(rhs)
{
}

CSecondFlagpole::~CSecondFlagpole()
{
}

HRESULT CSecondFlagpole::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}

CSecondFlagpole* CSecondFlagpole::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSecondFlagpole* pInstance = new CSecondFlagpole(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSecondFlagpole::Free()
{
	CFlagpole::Free();
}


HRESULT CSecondFlagpole::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"SECONDFLAGMOVE"), E_FAIL);
	CFlagpole::Ready_GameObject();
	m_iHP = 10000.f;
	m_vTransform->m_vAngle.y = D3DXToRadian(90.f);
	return S_OK;
}

_int CSecondFlagpole::Update_GameObject(const _float& fTimeDelta)
{


	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CSecondFlagpole::LateUpdate_GameObject()
{
	CFlagpole::LateUpdate_GameObject();
}

void CSecondFlagpole::Render_GameObject()
{
	CFlagpole::Render_GameObject();
}

