#include "stdafx.h"
#include "..\Header\StoreUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "StoreUIState1.h"

#include "SwordButton.h"
#include "BowButton.h"
#include "MageButton.h"
#include "ShieldButton.h"
#include "PriestButton.h"

#include "SwordMasterButton.h"
#include "ArchMageButton.h"
#include "HighPriestButton.h"
#include "ShooterButton.h"

#include "Emerald.h"

#include "RAButton.h"
#include "LAButton.h"

#include "FirstSquadButton.h"
#include "SecondSquadButton.h"
#include "ThirdSquadButton.h"
#include "FourthSquadButton.h"

CStoreUI::CStoreUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
	ZeroMemory(m_iSoldierPrice, sizeof(m_iSoldierPrice));
	ZeroMemory(m_bFontRenderCheck, sizeof(m_bFontRenderCheck));
}

CStoreUI::CStoreUI(const CStoreUI& rhs)
	: CControlUI(rhs)
{
}

CStoreUI::~CStoreUI()
{
}


HRESULT CStoreUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_StateBox"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);

	//m_iTextureNum = 0;

	//FAILED_CHECK_RETURN(CStoreUI::Create_ItemImage(), E_FAIL);

	m_pUIState = CStoreUIState1::Create(this);
	//m_eUI_RenderType = UIORDER::WINDOWUI;
	Set_UI_RenderType(UIORDER::WINDOWUI);
	return S_OK;
}

_int CStoreUI::Update_GameObject(const _float& fTimeDelta)
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

void CStoreUI::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}

HRESULT CStoreUI::Create_ItemImage()
{
	_vec3 vScale = { 40.f, 40.f,1.f };
	_vec3 vFrameScale = { 32.f, 32.f, 1.f };



	CGameObject* pGameObject = nullptr;

	if (m_eStateType == STATETYPE::TYPE_1) {

		pGameObject = CSwordButton::Create(m_pGraphicDev, SWORD_SOLDIER_COST);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(_vec3(-200.f, 20.f, 1.f));
		pGameObject->Get_Transform()->Set_Scale(vScale);
		static_cast<CSwordButton*>(pGameObject)->Set_OwnerUI(this);
		m_vecItemImage.push_back(pGameObject);

		m_bFontRenderCheck[0] = true;

		pGameObject = CEmerald::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-220.f, -50.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
			m_vecItemImage.push_back(pGameObject);

			

		if (CResourceMgr::GetInstance()->Get_Build_Existence(BUILDTYPE::SCHOOL)) {

			pGameObject = CBowButton::Create(m_pGraphicDev, BOW_SOLDIER_COST);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-100.f, 20.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(vScale);
			static_cast<CBowButton*>(pGameObject)->Set_OwnerUI(this);
			m_vecItemImage.push_back(pGameObject);

			m_bFontRenderCheck[1] = true;

			pGameObject = CEmerald::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-120.f, -50.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
			m_vecItemImage.push_back(pGameObject);

			pGameObject = CShieldButton::Create(m_pGraphicDev, SHIELD_SOLDIER_COST);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(0.f, 20.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(vScale);
			static_cast<CShieldButton*>(pGameObject)->Set_OwnerUI(this);
			m_vecItemImage.push_back(pGameObject);

			m_bFontRenderCheck[2] = true;

			pGameObject = CEmerald::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-20.f, -50.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
			m_vecItemImage.push_back(pGameObject);
		}

		if (CResourceMgr::GetInstance()->Get_Build_Existence(BUILDTYPE::MAGICSCHOOL)) {

			pGameObject = CMageButton::Create(m_pGraphicDev, MAGE_SOLDIER_COST);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(100.f, 20.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(vScale);
			static_cast<CMageButton*>(pGameObject)->Set_OwnerUI(this);
			m_vecItemImage.push_back(pGameObject);

			m_bFontRenderCheck[3] = true;

			pGameObject = CEmerald::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(80.f, -50.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
			m_vecItemImage.push_back(pGameObject);

			pGameObject = CPriestButton::Create(m_pGraphicDev, PRIEST_SOLDIER_COST);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(200.f, 20.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(vScale);
			static_cast<CPriestButton*>(pGameObject)->Set_OwnerUI(this);
			m_vecItemImage.push_back(pGameObject);

			m_bFontRenderCheck[4] = true;

			pGameObject = CEmerald::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(180.f, -50.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
			m_vecItemImage.push_back(pGameObject);

		}

		/*for (_int i = 0; i < 5; i++) {
			pGameObject = CEmerald::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-260.f + (i * 120), -80.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
			m_vecItemImage.push_back(pGameObject);
		}*/

		pGameObject = CRAButton::Create(m_pGraphicDev,this);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(_vec3(250.f, 150.f, 1.f));
		pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
		m_vecItemImage.push_back(pGameObject);

		if (CResourceMgr::GetInstance()->Get_Build_Existence(BUILDTYPE::COMMANDPOST)) {
			pGameObject = CFirstSquadButton::Create(m_pGraphicDev, this);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-200.f, 150.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(50.f, 30.f, 1.f));
			m_vecItemImage.push_back(pGameObject);

			pGameObject = CSecondSquadButton::Create(m_pGraphicDev, this);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-100.f, 150.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(50.f, 30.f, 1.f));
			m_vecItemImage.push_back(pGameObject);

			pGameObject = CThirdSquadButton::Create(m_pGraphicDev, this);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(0.f, 150.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(50.f, 30.f, 1.f));
			m_vecItemImage.push_back(pGameObject);

			pGameObject = CFourthSquadButton::Create(m_pGraphicDev, this);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(100.f, 150.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(50.f, 30.f, 1.f));
			m_vecItemImage.push_back(pGameObject);

			
		}

	}
	else if (m_eStateType == STATETYPE::TYPE_2) {
		if (CResourceMgr::GetInstance()->Get_Build_Existence(BUILDTYPE::COMMANDPOST)) {
			//if (!CSquardMgr::GetInstance()->Is_Commender_Buy_It(WEAPONTYPE::SWORD)) {
			pGameObject = CSwordMasterButton::Create(m_pGraphicDev, SWORDMASTER_COST);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-200.f, 20.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(vScale);
			m_vecItemImage.push_back(pGameObject);
			pGameObject = CEmerald::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-220.f, -50.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
			m_vecItemImage.push_back(pGameObject);
			//}

			//if (!CSquardMgr::GetInstance()->Is_Commender_Buy_It(WEAPONTYPE::BOW)) {
			pGameObject = CShooterButton::Create(m_pGraphicDev, SHOOTER_COST);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-100.f, 20.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(vScale);
			m_vecItemImage.push_back(pGameObject);
			pGameObject = CEmerald::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-120.f, -50.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
			m_vecItemImage.push_back(pGameObject);
			//}

			//if(!CSquardMgr::GetInstance()->Is_Commender_Buy_It(WEAPONTYPE::WAND)) {
			pGameObject = CArchMageButton::Create(m_pGraphicDev, ARCMAGE_COST);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(0.f, 20.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(vScale);
			m_vecItemImage.push_back(pGameObject);
			pGameObject = CEmerald::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(-20.f, -50.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
			m_vecItemImage.push_back(pGameObject);
			//}

			//if(!CSquardMgr::GetInstance()->Is_Commender_Buy_It(WEAPONTYPE::CROSS)) {
			pGameObject = CHighPriestButton::Create(m_pGraphicDev, HIGHPRIEST_COST);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(100.f, 20.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(vScale);
			m_vecItemImage.push_back(pGameObject);
			pGameObject = CEmerald::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pGameObject, E_FAIL);
			pGameObject->Get_Transform()->Set_Pos(_vec3(80.f, -50.f, 1.f));
			pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
			m_vecItemImage.push_back(pGameObject);
			//}

			for (_int i = 0; i < 4; i++) {
				m_bFontRenderCheck[i + 4] = true;
			}

			/*for (_int i = 0; i < 4; i++) {
				pGameObject = CEmerald::Create(m_pGraphicDev);
				NULL_CHECK_RETURN(pGameObject, E_FAIL);
				pGameObject->Get_Transform()->Set_Pos(_vec3(-260.f + (i * 120), -80.f, 1.f));
				pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
				m_vecItemImage.push_back(pGameObject);
			}*/
		}
		
		pGameObject = CLAButton::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(_vec3(-250.f, 150.f, 1.f));
		pGameObject->Get_Transform()->Set_Scale(_vec3(16.f, 16.f, 1.f));
		m_vecItemImage.push_back(pGameObject);
	}

	return S_OK;
}

CStoreUI* CStoreUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStoreUI* pInstance = new CStoreUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ItemBox Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CStoreUI::Render_GameObject()
{
	CControlUI::Render_GameObject();

	if (m_eStateType == STATETYPE::TYPE_1) {

		_int costArr[5] = { SWORD_SOLDIER_COST, BOW_SOLDIER_COST, MAGE_SOLDIER_COST, PRIEST_SOLDIER_COST, SHIELD_SOLDIER_COST  };

		for (_int i = 0; i < 5; i++) {

			if (m_bFontRenderCheck[i] == false)
				continue;

			_vec2 vPos2 = { 195.f + (i * 100), 335.f };
			_tchar srText[100] = {};
			swprintf_s(srText, L"%d", costArr[i]);
			Engine::Render_Font(L"Font_SotreCostUI", srText, &vPos2, D3DXCOLOR(0.f, 0.f, 0.f, 1.f));
		}
	}
	else if (m_eStateType == STATETYPE::TYPE_2) {
		_int costArr[4] = { SWORDMASTER_COST,SHOOTER_COST, ARCMAGE_COST, HIGHPRIEST_COST  };

		for (_int i = 0; i < 4; i++) {

			if (m_bFontRenderCheck[i+4] == false)
				continue;

			_vec2 vPos2 = { 195.f + (i * 100), 335.f };
			_tchar srText[100] = {};
			swprintf_s(srText, L"%d", costArr[i]);
			Engine::Render_Font(L"Font_SotreCostUI", srText, &vPos2, D3DXCOLOR(0.f, 0.f, 0.f, 1.f));
		}
	}
}

void CStoreUI::Free()
{
	CControlUI::Free();
}

HRESULT CStoreUI::Add_Component()
{
	return S_OK;
}
