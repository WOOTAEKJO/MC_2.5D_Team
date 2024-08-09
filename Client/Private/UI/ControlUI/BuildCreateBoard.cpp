#include "stdafx.h"
#include "..\Header\BuildCreateBoard.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "StoreUIState1.h"

#include "SwordButton.h"
#include "BowButton.h"

#include "BuildRAButton.h"
#include "BuildLAButton.h"
#include "StoreCreateButton.h"
#include "SchoolCreateButton.h"
#include "MagicSchoolCreateButton.h"
#include "CommandPostCreateButton.h"
#include "AttackTowerCreateButton.h"
#include "MagicAttackTowerCreateButton.h"
#include "Trap1CreateButton.h"
#include "Trap2CreateButton.h"
#include "Trap3CreateButton.h"

#include "Emerald.h"

#include "BuildCreateState1.h"

CBuildCreateBoard::CBuildCreateBoard(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
	ZeroMemory(m_iBuildCost, sizeof(m_iBuildCost));
}

CBuildCreateBoard::CBuildCreateBoard(const CBuildCreateBoard& rhs)
	: CControlUI(rhs)
{
}

CBuildCreateBoard::~CBuildCreateBoard()
{
}


HRESULT CBuildCreateBoard::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_Board"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	//FAILED_CHECK_RETURN(CBuildCreateBoard::Create_ItemImage(), E_FAIL);

	m_pUIState = CBuildCreateState1::Create(this);

	for (_int i = 0; i < 9; i++) {
		m_iBuildCost[i] = CResourceMgr::GetInstance()->Get_Build_Cost((BUILDTYPE)(i + 2));
	}

	//m_eUI_RenderType = UIORDER::WINDOWUI;
	Set_UI_RenderType(UIORDER::WINDOWUI);
	return S_OK;
}

_int CBuildCreateBoard::Update_GameObject(const _float& fTimeDelta)
{
	CUIState* pUIState = m_pUIState->Update_State(this, fTimeDelta);
	if (pUIState != nullptr)
	{
		m_pUIState->Free(this);
		Safe_Delete(m_pUIState);
		m_pUIState = pUIState;
	}

	return CControlUI::Update_GameObject(fTimeDelta);
}

void CBuildCreateBoard::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}

void CBuildCreateBoard::Pick_Button(BUILDTYPE eType)
{
	/*if (m_bCollCheck) {

		_int iCost = CResourceMgr::GetInstance()->Get_Build_Cost(BUILDTYPE::STORE);
		if (iCost == -1) {
			m_bCollCheck = false;
			return 0;
		}

		if (CResourceMgr::GetInstance()->Get_Money() - iCost >= 0) {

			static_cast<CBuildCreateBoard*>(m_pConUI)
				->Set_BuildType(BUILDTYPE::STORE);

			m_bPick_Check = true;
			m_iTextureNum = 1;
			m_fCount = 0.f;
		}
		m_bCollCheck = false;
	}

	if (m_iTextureNum == 1) {
		if (m_fCount > 0.1f) {
			m_iTextureNum = 0;
			m_fCount = 0.f;
		}
	}

	if (m_bPick_Check) {

		if (static_cast<CBuildCreateBoard*>(m_pConUI)
			->Get_BuildType() != BUILDTYPE::STORE)
		{
			m_pBuildMap->Delete_PreView();
			m_bPick_Check = false;
		}

		m_pBuildMap->Show_PreView(BUILDTYPE::STORE);
	}*/
}

HRESULT CBuildCreateBoard::Create_ItemImage()
{
	_vec3 vScale = { 16.f, 16.f, 1.f };
	_vec3 vFrameScale = { 32.f, 32.f, 1.f };

	CGameObject* pGameObject = nullptr;

	switch (m_eStateType)
	{
	case CControlUI::TYPE_1:

			{
				_vec3 vPos = *m_vTransform->Get_Pos();
				pGameObject = CBuildRAButton::Create(m_pGraphicDev, this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(320.f,-250.f,1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(15.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				pGameObject = CStoreCreateButton::Create(m_pGraphicDev,this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(-250.f, -240.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(40.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				pGameObject = CCommandPostCreateButton::Create(m_pGraphicDev, this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(-100.f, -240.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(40.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				pGameObject = CMagicSchoolCreateButton::Create(m_pGraphicDev, this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(50.f, -240.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(40.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				pGameObject = CSchoolCreateButton::Create(m_pGraphicDev, this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(200.f, -240.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(40.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				for (_int i = 0; i < 4; i++) {
				pGameObject = CEmerald::Create(m_pGraphicDev);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(-280.f + (i*150.f), -280.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(10.f, 10.f, 1.f));
				m_vecItemImage.push_back(pGameObject);
				}
			}
		break;
	case CControlUI::TYPE_2:
			{
				_vec3 vPos = *m_vTransform->Get_Pos();
				pGameObject = CBuildLAButton::Create(m_pGraphicDev, this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(-320.f, -240.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(15.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				pGameObject = CAttackTowerCreateButton::Create(m_pGraphicDev, this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(-250.f, -240.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(40.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				pGameObject = CMagicAttackTowerCreateButton::Create(m_pGraphicDev, this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(-120.f, -240.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(40.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				pGameObject = CTrap1CreateButton::Create(m_pGraphicDev, this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(10.f, -240.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(40.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				pGameObject = CTrap2CreateButton::Create(m_pGraphicDev, this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(140.f, -240.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(40.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				pGameObject = CTrap3CreateButton::Create(m_pGraphicDev, this);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(270.f, -240.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(40.f, 30.f, 1.f));
				m_vecItemImage.push_back(pGameObject);

				for (_int i = 0; i < 5; i++) {
					pGameObject = CEmerald::Create(m_pGraphicDev);
					NULL_CHECK_RETURN(pGameObject, E_FAIL);
					pGameObject->Get_Transform()->Set_Pos(_vec3(-280.f + (i * 130.f), -280.f, 1.f));
					pGameObject->Get_Transform()->Set_Scale(_vec3(10.f, 10.f, 1.f));
					m_vecItemImage.push_back(pGameObject);
				}
			}
		break;
	}

	return S_OK;
}

CBuildCreateBoard* CBuildCreateBoard::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBuildCreateBoard* pInstance = new CBuildCreateBoard(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ItemBox Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CBuildCreateBoard::Render_GameObject()
{
	CControlUI::Render_GameObject();

	switch (m_eStateType)
	{
	case CControlUI::TYPE_1:
		for (_int i = 0; i < 4; i++) {
			_vec2 vPos2 = { 130.f + (i*150.f), 573.f };
			_tchar srTest[100] = {};
			swprintf_s(srTest, L"x%d", m_iBuildCost[i]);
			Engine::Render_Font(L"Font_BuildCostUI", srTest, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		}
		break;
	case CControlUI::TYPE_2:
		for (_int i = 0; i < 5; i++) {
			_vec2 vPos2 = { 130.f + (i*130.f), 573.f };
			_tchar srTest[100] = {};
			swprintf_s(srTest, L"x%d", m_iBuildCost[i+4]);
			Engine::Render_Font(L"Font_BuildCostUI", srTest, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		}
		break;
	}


	
}

void CBuildCreateBoard::Free()
{
	
	CControlUI::Free();
}

HRESULT CBuildCreateBoard::Add_Component()
{
	return S_OK;
}
