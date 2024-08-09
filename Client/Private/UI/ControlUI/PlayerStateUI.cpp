#include "stdafx.h"
#include "..\Header\PlayerStateUI.h"

#include "Export_Utility.h"

#include "SquardMgr.h"

#include "Character.h"

#include "Heart.h"

CPlayerStateUI::CPlayerStateUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CControlUI(pGraphicDev)
{
}

CPlayerStateUI::CPlayerStateUI(const CPlayerStateUI& rhs)
	: CControlUI(rhs)
{
}

CPlayerStateUI::~CPlayerStateUI()
{
}

HRESULT CPlayerStateUI::Ready_GameObject()
{
	//FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_Heart"), E_FAIL);
	FAILED_CHECK_RETURN(CControlUI::Ready_GameObject(), E_FAIL);
	FAILED_CHECK_RETURN(CPlayerStateUI::Create_ItemImage(), E_FAIL);
	//m_iTextureNum = 0;
	
	//m_eUI_RenderType = UIORDER::ALWAYSUI;
	Set_UI_RenderType(UIORDER::ALWAYSUI);
	return S_OK;
}

_int CPlayerStateUI::Update_GameObject(const _float& fTimeDelta)
{
	Player_HP_UI_Update();

	return CControlUI::Update_GameObject(fTimeDelta);
}

void CPlayerStateUI::LateUpdate_GameObject()
{
	CControlUI::LateUpdate_GameObject();
}


CPlayerStateUI* CPlayerStateUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerStateUI* pInstance = new CPlayerStateUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("Heart Create Failed");
		return nullptr;
	}

	return pInstance;
}


void CPlayerStateUI::Render_GameObject()
{
	//CUI::Render_GameObject();
}

HRESULT CPlayerStateUI::Create_ItemImage()
{
	CGameObject* pGameObject = nullptr;

	
	_vec3 vScale = { 8.f, 8.f, 1.f };
	
	
	for (_int i = 0; i < 10; i++) {
		pGameObject = CHeart::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pGameObject->Get_Transform()->Set_Pos(Cal_Pos(i));
		pGameObject->Get_Transform()->Set_Scale(vScale);
		m_vecItemImage.push_back(pGameObject);
	}

	return S_OK;
}

void CPlayerStateUI::Free()
{
	CControlUI::Free();
}

void CPlayerStateUI::Player_HP_UI_Update()
{
	//if (!m_bHP_Check) {
		//m_pPlayerInfo = Engine::CManagement::GetInstance()->Get_GameLogic_Objects(OBJECTTYPE::PLAYER).front();
		
		 //m_bHP_Check = true;
	//}
	
	SQUARD_ID eType = CSquardMgr::GetInstance()->Get_SelectedSquard();
	if (eType == SQUARD_ID_END)
		return;

	m_pPlayerInfo = CSquardMgr::GetInstance()->Get_SquardCommander(eType);

	if (m_pPlayerInfo == nullptr || m_pPlayerInfo->Get_Dead() || m_pPlayerInfo->Get_ObjectType() !=
		OBJECTTYPE::PLAYER)
		return;

	m_iMaxHP = dynamic_cast<CCharacter*>(m_pPlayerInfo)->Get_MaxHP();

	_int iPlayerHP = dynamic_cast<CCharacter*>(m_pPlayerInfo)->Get_HP();
	
	if (iPlayerHP < 0)
		return;

	for (_int i = (iPlayerHP/ (m_iMaxHP / 10)); i < 10; i++) {
		CUI* pUI = dynamic_cast<CUI*>(m_vecItemImage[i]);

		if (i == 0) {
			if (iPlayerHP <= 0) {
				pUI->Set_TextureNum(1);
			}
		}
		else {
			/*if (pUI->Get_TextureNum() == 0) {
				pUI->Set_TextureNum(1);
			}
			else if (pUI->Get_TextureNum() == 1) {
				pUI->Set_TextureNum(0);
			}*/
			pUI->Set_TextureNum(1);
		}
	}

	for (_int i = 0; i < (iPlayerHP / (m_iMaxHP / 10)); i++) {
		CUI* pUI = dynamic_cast<CUI*>(m_vecItemImage[i]);

		pUI->Set_TextureNum(0);

	}

	/*_int iNum = 10 - (iPlayerHP / (m_iMaxHP / 10));

	for (_int i = 0; i < iNum; i++) {

		CUI* pUI = dynamic_cast<CUI*>(m_vecItemImage[i]);

		if (i == 0) {
			if (iPlayerHP <= 0) {
				pUI->Set_TextureNum(1);
			}
		}
		else {
			
			pUI->Set_TextureNum(1);
		}
	}*/
}

HRESULT CPlayerStateUI::Add_Component()
{

	return S_OK;
}
