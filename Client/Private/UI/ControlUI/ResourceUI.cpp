#include "stdafx.h"
#include "..\Header\ResourceUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"

#include "Emerald.h"
#include "ResourceMgr.h"

CResourceUI::CResourceUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
}

CResourceUI::CResourceUI(const CResourceUI& rhs)
	: CControlUI(rhs)
{
}

CResourceUI::~CResourceUI()
{
}


HRESULT CResourceUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_ResourceBox"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);

	m_vTransform->Set_Pos(_vec3(320.f, 280.f, 1.f));
	m_vTransform->Set_Scale(_vec3(120.f, 15.f, 1.f));

	m_iTextureNum = 0;

	FAILED_CHECK_RETURN(CResourceUI::Create_ItemImage(), E_FAIL);

	//m_pUIState = CResourceUIState1::Create(this);
	//m_eUI_RenderType = UIORDER::ALWAYSUI;
	Set_UI_RenderType(UIORDER::ALWAYSUI);
	return S_OK;
}

_int CResourceUI::Update_GameObject(const _float& fTimeDelta)
{
	/*CUIState* pUIState = m_pUIState->Update_State(this, fTimeDelta);
	if (pUIState != nullptr)
	{
		m_pUIState->Free(this);
		Safe_Delete(m_pUIState);
		m_pUIState = pUIState;
	}*/

	return CControlUI::Update_GameObject(fTimeDelta);
}

void CResourceUI::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}

HRESULT CResourceUI::Create_ItemImage()
{
	_vec3 vPos = *m_vTransform->Get_Pos();
	_vec3 vScale = *m_vTransform->Get_Scale();

	CGameObject* pGameObject = nullptr;

	pGameObject = CEmerald::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pGameObject->Get_Transform()->Set_Pos(_vec3(vPos.x - vScale.x + 70.f, vPos.y, 1.f));
	pGameObject->Get_Transform()->Set_Scale(_vec3(15.f, 15.f, 1.f));
	m_vecItemImage.push_back(pGameObject);

	return S_OK;
}

CResourceUI* CResourceUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CResourceUI* pInstance = new CResourceUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ItemBox Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CResourceUI::Render_GameObject()
{
	CControlUI::Render_GameObject();

	_vec2 vPos2 = { 685.f, 11.f };
	_int  iMoney = CResourceMgr::GetInstance()->Get_Money();
	_tchar srTest[100] = {};
	swprintf_s(srTest, L"X%d", iMoney);
	Engine::Render_Font(L"Font_ResourceUI", srTest, &vPos2, D3DXCOLOR(0.f, 0.f, 0.f, 1.f));
}

void CResourceUI::Free()
{
	CControlUI::Free();
}

HRESULT CResourceUI::Add_Component()
{
	return S_OK;
}
