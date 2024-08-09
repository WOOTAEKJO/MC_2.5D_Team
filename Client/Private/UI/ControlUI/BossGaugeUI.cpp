#include "stdafx.h"
#include "..\Header\BossGaugeUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"

#include "BossGauge.h"
#include "ResourceMgr.h"

CBossGaugeUI::CBossGaugeUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
}

CBossGaugeUI::CBossGaugeUI(const CBossGaugeUI& rhs)
	: CControlUI(rhs)
{
}

CBossGaugeUI::~CBossGaugeUI()
{
}


HRESULT CBossGaugeUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BossBar"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);

	//m_vTransform->Set_Pos(_vec3(330.f, 275.f, 1.f));
	//m_vTransform->Set_Scale(_vec3(20.f, 20.f, 1.f));

	m_iTextureNum = 0;

	

	//m_pUIState = CBossGaugeUIState1::Create(this);
	//m_eUI_RenderType = UIORDER::ALWAYSUI;
	Set_UI_RenderType(UIORDER::ALWAYSUI);
	return S_OK;
}

_int CBossGaugeUI::Update_GameObject(const _float& fTimeDelta)
{
	/*CUIState* pUIState = m_pUIState->Update_State(this, fTimeDelta);
	if (pUIState != nullptr)
	{
		m_pUIState->Free(this);
		Safe_Delete(m_pUIState);
		m_pUIState = pUIState;
	}*/
	if (m_vecItemImage.empty()) {
		FAILED_CHECK_RETURN(CBossGaugeUI::Create_ItemImage(), -1);
	}


	return CControlUI::Update_GameObject(fTimeDelta);
}

void CBossGaugeUI::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}

HRESULT CBossGaugeUI::Create_ItemImage()
{
	_vec3 vPos = *m_vTransform->Get_Pos();
	_vec3 vScale = (*m_vTransform->Get_Scale());

	_vec3 vEndPoint = vPos + (vScale * 0.7f);
	_vec3 vStartPoint = vPos - (vScale * 0.7f) ;

	vPos.y -= 3.f;
	vPos.x -= vScale.x * 0.7f;

	vScale.x *= 0.f;
	vScale.y *= 0.4f;
	
	CGameObject* pGameObject = nullptr;

	pGameObject = CBossGauge::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pGameObject->Get_Transform()->Set_Pos(vPos);
	pGameObject->Get_Transform()->Set_Scale(vScale);
	dynamic_cast<CBossGauge*>(pGameObject)->Set_End_Point(vEndPoint);
	dynamic_cast<CBossGauge*>(pGameObject)->Set_Start_Point(vStartPoint);
	m_vecItemImage.push_back(pGameObject);

	return S_OK;
}

CBossGaugeUI* CBossGaugeUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBossGaugeUI* pInstance = new CBossGaugeUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ItemBox Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CBossGaugeUI::Render_GameObject()
{
	CControlUI::Render_GameObject();

	/*_vec2 vPos2 = { 700.f,16.f };
	_int  iMoney = CResourceMgr::GetInstance()->Get_Money();
	_tchar srTest[100] = {};
	swprintf_s(srTest, L"X %d", iMoney);
	Engine::Render_Font(L"Font_ResourceUI", srTest, &vPos2, D3DXCOLOR(0.f, 0.f, 0.f, 1.f));*/
}

void CBossGaugeUI::Free()
{
	CControlUI::Free();
}

HRESULT CBossGaugeUI::Add_Component()
{
	return S_OK;
}
