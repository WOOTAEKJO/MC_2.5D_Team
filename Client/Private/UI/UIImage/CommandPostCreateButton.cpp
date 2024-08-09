#include "stdafx.h"
#include "..\Header\CommandPostCreateButton.h"

#include "Export_System.h"
#include "Export_Utility.h"
#include "ObjCreationMgr.h"
#include "BuildMap.h"

#include "Store.h"

#include "BowSoldier.h"

#include "ResourceMgr.h"
#include "CurrentModeMgr.h"
#include "F_DynamicCamera.h"

#include "BuildCreateBoard.h"

CCommandPostCreateButton::CCommandPostCreateButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CCommandPostCreateButton::CCommandPostCreateButton(const CCommandPostCreateButton& rhs)
	: CUIImage(rhs)
{
}

CCommandPostCreateButton::~CCommandPostCreateButton()
{
}

HRESULT CCommandPostCreateButton::Ready_GameObject(CUI* pUI)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_CommandPostImage"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	m_pBuildMap = dynamic_cast<CBuildMap*>(Engine::CManagement::GetInstance()
		->Get_Environment_Objects(OBJECTTYPE::BUILDMAP).front());
	NULL_CHECK(m_pBuildMap);

	m_pConUI = pUI;

	return S_OK;
}

_int CCommandPostCreateButton::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_bCollCheck) {
		_int iCost = CResourceMgr::GetInstance()->Get_Build_Cost(BUILDTYPE::COMMANDPOST);
		if (iCost == -1) {
			m_bCollCheck = false;
			return 0;
		}

		if (CResourceMgr::GetInstance()->Get_Money() - iCost >= 0) {
			static_cast<CBuildCreateBoard*>(m_pConUI)
				->Set_BuildType(BUILDTYPE::COMMANDPOST);
			m_bPick_Check = true;
			//m_bHide = true;

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
			->Get_BuildType() != BUILDTYPE::COMMANDPOST)
		{
			m_pBuildMap->Delete_PreView();
			m_bPick_Check = false;
		}

		m_pBuildMap->Show_PreView(BUILDTYPE::COMMANDPOST);
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CCommandPostCreateButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CCommandPostCreateButton::Render_GameObject()
{
	CUIImage::Render_GameObject();

	_vec3 vPos = *m_vTransform->Get_Pos();
	_vec3 vScale = *m_vTransform->Get_Scale();
	//_vec2 vPos2 = { vPos.x, vPos.y };
	_vec2 vPos2 = { 260.f, 535.f };
	_tchar srTest[100] = {};
	swprintf_s(srTest, L"ÁöÈÖ¼Ò");
	Engine::Render_Font(L"Font_ResourceUI", srTest, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

HRESULT CCommandPostCreateButton::Add_Component()
{

	return S_OK;
}

CCommandPostCreateButton* CCommandPostCreateButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI)
{
	CCommandPostCreateButton* pInstance = new CCommandPostCreateButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pUI))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCommandPostCreateButton::Free()
{
	m_pBuildMap->Delete_PreView();
	CUIImage::Free();
}
