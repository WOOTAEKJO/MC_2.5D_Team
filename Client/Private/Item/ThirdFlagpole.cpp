#include "stdafx.h"
#include "..\Header\ThirdFlagpole.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CThirdFlagpole::CThirdFlagpole(LPDIRECT3DDEVICE9 pGraphicDev)
	:CFlagpole(pGraphicDev)
{
}

CThirdFlagpole::CThirdFlagpole(const CThirdFlagpole& rhs)
	: CFlagpole(rhs)
{
}

CThirdFlagpole::~CThirdFlagpole()
{
}

HRESULT CThirdFlagpole::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}

CThirdFlagpole* CThirdFlagpole::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CThirdFlagpole* pInstance = new CThirdFlagpole(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CThirdFlagpole::Free()
{
	CFlagpole::Free();
}


HRESULT CThirdFlagpole::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"THIRDFLAGMOVE"), E_FAIL);
	CFlagpole::Ready_GameObject();
	m_iHP = 10000.f;
	m_vTransform->m_vAngle.y = D3DXToRadian(90.f);
	return S_OK;
}

_int CThirdFlagpole::Update_GameObject(const _float& fTimeDelta)
{


	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CThirdFlagpole::LateUpdate_GameObject()
{
	CFlagpole::LateUpdate_GameObject();
}

void CThirdFlagpole::Render_GameObject()
{
	CFlagpole::Render_GameObject();
}

