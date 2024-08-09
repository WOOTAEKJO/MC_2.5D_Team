#include "stdafx.h"
#include "..\Header\Meat.h"

#include "Export_Utility.h"

CMeat::CMeat(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
}

CMeat::CMeat(const CMeat& rhs)
	: CUI(rhs)
{
}

CMeat::~CMeat()
{
}

HRESULT CMeat::Ready_GameObject(_int iCount)
{

	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_Meat"), E_FAIL);
	FAILED_CHECK_RETURN(CUI::Ready_GameObject(), E_FAIL);
	
	//m_pTransformCom->Set_Scale(0.15f, 0.15f);
	//m_pTransformCom->Set_Pos(1.0f + (iCount * 0.3f), -4.3f, 10.f);

	m_iTextureNum = 0;

	return S_OK;
}

_int CMeat::Update_GameObject(const _float& fTimeDelta)
{

	return CUI::Update_GameObject(fTimeDelta);
}

void CMeat::LateUpdate_GameObject()
{
	CUI::LateUpdate_GameObject();
}

CMeat* CMeat::Create(LPDIRECT3DDEVICE9 pGraphicDev, _int iCount)
{
	CMeat* pInstance = new CMeat(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(iCount))) {
		Safe_Release(pInstance);

		MSG_BOX("Meat Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMeat::Render_GameObject()
{
	CUI::Render_GameObject();
}

void CMeat::Free()
{
	CUI::Free();
}

HRESULT CMeat::Add_Component()
{
	return S_OK;
}
