#include "stdafx.h"
#include "..\Header\BossNameBox.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "BossGauge.h"
#include "BossStateUI.h"

#include "Rich.h"

CBossNameBox::CBossNameBox(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
}

CBossNameBox::CBossNameBox(const CBossNameBox& rhs)
	: CControlUI(rhs)
{
}

CBossNameBox::~CBossNameBox()
{
}


HRESULT CBossNameBox::Ready_GameObject(CGameObject* pOwner)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BossNameBox"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	m_vTransform->m_vAngle.z = D3DXToRadian(45.f);

	m_pOwner = pOwner;
	NULL_CHECK_RETURN(pOwner,E_FAIL);
	//m_eUI_RenderType = UIORDER::ALWAYSUI;
	Set_UI_RenderType(UIORDER::ALWAYSUI);
	return S_OK;
}

_int CBossNameBox::Update_GameObject(const _float& fTimeDelta)
{
	/*CUIState* pUIState = m_pUIState->Update_State(this, fTimeDelta);
	if (pUIState != nullptr)
	{
		m_pUIState->Free(this);
		Safe_Delete(m_pUIState);
		m_pUIState = pUIState;
	}*/
	if (m_vecItemImage.empty()) {
		FAILED_CHECK_RETURN(CBossNameBox::Create_ItemImage(), -1);
	}

	return CControlUI::Update_GameObject(fTimeDelta);
}

void CBossNameBox::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}

HRESULT CBossNameBox::Create_ItemImage()
{
	_vec3 vPos = *m_vTransform->Get_Pos();
	_vec3 vScale = (*m_vTransform->Get_Scale());
	vScale *= 0.7f;
	CGameObject* pGameObject = nullptr;

	pGameObject = CBossStateUI::Create(m_pGraphicDev,this);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pGameObject->Get_Transform()->Set_Pos(vPos);
	pGameObject->Get_Transform()->Set_Scale(vScale);
	m_vecItemImage.push_back(pGameObject);

	return S_OK;
}

_bool CBossNameBox::Is_Change_State()
{
	if (m_pOwner == nullptr || m_pOwner->Get_Dead())
		return false;

	if (static_cast<CRich*>(m_pOwner)->Get_PhaseType() == CRich::RICHPHASETYPE::PHASE2) {
		return true;
	}

	return false;
}

CBossNameBox* CBossNameBox::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner)
{
	CBossNameBox* pInstance = new CBossNameBox(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pOwner))) {
		Safe_Release(pInstance);

		MSG_BOX("ItemBox Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CBossNameBox::Render_GameObject()
{
	CControlUI::Render_GameObject();

	/*_vec2 vPos2 = { 700.f,16.f };
	_int  iMoney = CResourceMgr::GetInstance()->Get_Money();
	_tchar srTest[100] = {};
	swprintf_s(srTest, L"X %d", iMoney);
	Engine::Render_Font(L"Font_ResourceUI", srTest, &vPos2, D3DXCOLOR(0.f, 0.f, 0.f, 1.f));*/

	_vec2 vPos2 = { 360.f, 10.f };
	_tchar srText[100] = {};
	swprintf_s(srText, L"¸®Ä¡");
	Engine::Render_Font(L"Font_BossName", srText, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

void CBossNameBox::Free()
{
	CControlUI::Free();
}

HRESULT CBossNameBox::Add_Component()
{
	return S_OK;
}
