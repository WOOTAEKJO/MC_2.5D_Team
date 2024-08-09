#include "stdafx.h"
#include "..\Header\ItemBox.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"

#include "SwordItemImage.h"
#include "BowItemImage.h"
#include "PlayerStateUI.h"

#include "FrameUI.h"

#include "CurrentModeMgr.h"

#include "ItemBoxUIState.h"

CItemBox::CItemBox(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
}

CItemBox::CItemBox(const CItemBox& rhs)
	: CControlUI(rhs)
{
}

CItemBox::~CItemBox()
{
}


HRESULT CItemBox::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_ItemBox"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);

	m_vTransform->Set_Scale(_vec3(256.f,32.f,1.f));
	m_vTransform->Set_Pos(_vec3(0.f, -260.f, 1.f));
	m_iTextureNum = 0;

	//FAILED_CHECK_RETURN(CItemBox::Create_ItemImage(), E_FAIL);

	m_pUIState = CItemBoxUIState::Create(this);

	//m_eUI_RenderType = UIORDER::ALWAYSUI;
	Set_UI_RenderType(UIORDER::ALWAYSUI);
	return S_OK;
}

_int CItemBox::Update_GameObject(const _float& fTimeDelta)
{
	
	CUIState* pUIState = m_pUIState->Update_State(this, fTimeDelta);
	if (pUIState != nullptr)
	{
		m_pUIState->Free(this);
		Safe_Delete(m_pUIState);
		m_pUIState = pUIState;
	}

	FrameUI_KeyInput();

	return CControlUI::Update_GameObject(fTimeDelta);
}

void CItemBox::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}

HRESULT CItemBox::Create_ItemImage()
{
	_vec3 vScale = { 16.f, 16.f, 1.f };
	_vec3 vFrameScale = { 32.f, 32.f,1.f };
	
	CGameObject* pGameObject = nullptr;

	pGameObject = CFrameUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pGameObject->Get_Transform()->Set_Pos(Cal_Pos(0));
	pGameObject->Get_Transform()->Set_Scale(vFrameScale);
	m_vecItemImage.push_back(pGameObject);
	
	if (m_eWeaponType == WEAPONTYPE::SWORD) {

		pGameObject = CSwordItemImage::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(Cal_Pos(0));
		pGameObject->Get_Transform()->Set_Scale(vScale);
		m_vecItemImage.push_back(pGameObject);
	}
	else if (m_eWeaponType == WEAPONTYPE::BOW) {
		pGameObject = CBowItemImage::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(Cal_Pos(0));
		pGameObject->Get_Transform()->Set_Scale(vScale);
		m_vecItemImage.push_back(pGameObject);
	}
	else if (m_eWeaponType == WEAPONTYPE::WAND) {

	}
	else if (m_eWeaponType == WEAPONTYPE::CROSS) {

	}

	return S_OK;
}

void CItemBox::FrameUI_KeyInput()
{
	if (CCurrentModeMgr::GetInstance()->Get_Current_State_ID() == CURRENTSTATEID::NORMAL) 
	{
		if (m_vecItemImage.empty())
			return;

		if (Engine::Key_Down(DIK_1)) {
			m_vecItemImage.front()->Get_Transform()->Set_Pos(Cal_Pos(0));
		}
		else if (Engine::Key_Down(DIK_2)) {

			m_vecItemImage.front()->Get_Transform()->Set_Pos(Cal_Pos(1));
		}
		else if (Engine::Key_Down(DIK_3)) {

			m_vecItemImage.front()->Get_Transform()->Set_Pos(Cal_Pos(2));
		}
		else if (Engine::Key_Down(DIK_4)) {

			m_vecItemImage.front()->Get_Transform()->Set_Pos(Cal_Pos(3));
		}
		else if (Engine::Key_Down(DIK_5)) {

			m_vecItemImage.front()->Get_Transform()->Set_Pos(Cal_Pos(4));
		}
		else if (Engine::Key_Down(DIK_6)) {

			m_vecItemImage.front()->Get_Transform()->Set_Pos(Cal_Pos(5));
		}
		else if (Engine::Key_Down(DIK_7)) {

			m_vecItemImage.front()->Get_Transform()->Set_Pos(Cal_Pos(6));
		}
		else if (Engine::Key_Down(DIK_8)) {

			m_vecItemImage.front()->Get_Transform()->Set_Pos(Cal_Pos(7));
		}
		else if (Engine::Key_Down(DIK_9)) {

			m_vecItemImage.front()->Get_Transform()->Set_Pos(Cal_Pos(8));
		}
	}

}

CItemBox* CItemBox::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CItemBox* pInstance = new CItemBox(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ItemBox Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CItemBox::Render_GameObject()
{
	if (!CSquardMgr::GetInstance()->Is_Squard_Exist()) {
		if (CSquardMgr::GetInstance()->Get_SelectedSquard() != SQUARD_ID_END) {
			CControlUI::Render_GameObject();
		}
	}
}

void CItemBox::Free()
{
	CControlUI::Free();
}

HRESULT CItemBox::Add_Component()
{
	return S_OK;
}
