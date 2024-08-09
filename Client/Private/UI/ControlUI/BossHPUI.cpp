#include "stdafx.h"
#include "..\Header\BossHPUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"

#include "BossHP.h"
#include "ResourceMgr.h"

CBossHPUI::CBossHPUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
}

CBossHPUI::CBossHPUI(const CBossHPUI& rhs)
	: CControlUI(rhs)
{
}

CBossHPUI::~CBossHPUI()
{
}


HRESULT CBossHPUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BossBar"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);

	//m_vTransform->Set_Pos(_vec3(10.f, 265.f, 1.f));
	//m_vTransform->Set_Scale(_vec3(270.f, 15.f, 1.f));

	m_iTextureNum = 0;

	//m_pUIState = CBossHPUIState1::Create(this);
	//m_eUI_RenderType = UIORDER::ALWAYSUI;
	Set_UI_RenderType(UIORDER::ALWAYSUI);
	return S_OK;
}

_int CBossHPUI::Update_GameObject(const _float& fTimeDelta)
{
	/*CUIState* pUIState = m_pUIState->Update_State(this, fTimeDelta);
	if (pUIState != nullptr)
	{
		m_pUIState->Free(this);
		Safe_Delete(m_pUIState);
		m_pUIState = pUIState;
	}*/
	if (m_vecItemImage.empty()) {
		FAILED_CHECK_RETURN(CBossHPUI::Create_ItemImage(), E_FAIL);
	}

	return CControlUI::Update_GameObject(fTimeDelta);
}

void CBossHPUI::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}

void CBossHPUI::Is_Rich_Alive()
{
	
}

HRESULT CBossHPUI::Create_ItemImage()
{
	_vec3 vPos = *m_vTransform->Get_Pos();
	_vec3 vScale = (*m_vTransform->Get_Scale());

	vScale.x *= 0.7f;
	vScale.y *= 0.35f;
	vScale.z *= 0.5f;

	vPos.y -= 2.f;

	CGameObject* pGameObject = nullptr;

	pGameObject = CBossHP::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pGameObject->Get_Transform()->Set_Pos(vPos);
	pGameObject->Get_Transform()->Set_Scale(vScale);
	m_vecItemImage.push_back(pGameObject);

	return S_OK;
}

CBossHPUI* CBossHPUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBossHPUI* pInstance = new CBossHPUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ItemBox Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CBossHPUI::Render_GameObject()
{
	CControlUI::Render_GameObject();

	/*_vec2 vPos2 = { 700.f,16.f };
	_int  iMoney = CResourceMgr::GetInstance()->Get_Money();
	_tchar srTest[100] = {};
	swprintf_s(srTest, L"X %d", iMoney);
	Engine::Render_Font(L"Font_ResourceUI", srTest, &vPos2, D3DXCOLOR(0.f, 0.f, 0.f, 1.f));*/
}

void CBossHPUI::Free()
{
	CControlUI::Free();
}

HRESULT CBossHPUI::Add_Component()
{
	return S_OK;
}
