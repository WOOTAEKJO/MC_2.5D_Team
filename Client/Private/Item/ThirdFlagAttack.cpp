#include "stdafx.h"
#include "..\Header\ThirdFlagAttack.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "Player.h"

CThirdFlagAttack::CThirdFlagAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	:CFlagpole(pGraphicDev)
{
}

CThirdFlagAttack::CThirdFlagAttack(const CThirdFlagAttack& rhs)
	: CFlagpole(rhs)
{
}

CThirdFlagAttack::~CThirdFlagAttack()
{
}

HRESULT CThirdFlagAttack::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}

CThirdFlagAttack* CThirdFlagAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CThirdFlagAttack* pInstance = new CThirdFlagAttack(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Sword Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CThirdFlagAttack::Free()
{
	CFlagpole::Free();
}


HRESULT CThirdFlagAttack::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Set_Item(L"THIRDFLAGATK"), E_FAIL);
	CFlagpole::Ready_GameObject();
	m_iHP = 10000.f;
	m_vTransform->m_vAngle.y = D3DXToRadian(90.f);
	return S_OK;
}

_int CThirdFlagAttack::Update_GameObject(const _float& fTimeDelta)
{


	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CThirdFlagAttack::LateUpdate_GameObject()
{
	CFlagpole::LateUpdate_GameObject();
}

void CThirdFlagAttack::Render_GameObject()
{
	CFlagpole::Render_GameObject();
}

