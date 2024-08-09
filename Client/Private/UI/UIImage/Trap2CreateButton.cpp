#include "stdafx.h"
#include "..\Header\Trap2CreateButton.h"

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

CTrap2CreateButton::CTrap2CreateButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CTrap2CreateButton::CTrap2CreateButton(const CTrap2CreateButton& rhs)
	: CUIImage(rhs)
{
}

CTrap2CreateButton::~CTrap2CreateButton()
{
}

HRESULT CTrap2CreateButton::Ready_GameObject(CUI* pUI)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_Trap2Image"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	m_pBuildMap = dynamic_cast<CBuildMap*>(Engine::CManagement::GetInstance()
		->Get_Environment_Objects(OBJECTTYPE::BUILDMAP).front());
	NULL_CHECK(m_pBuildMap);

	m_pConUI = pUI;

	return S_OK;
}

_int CTrap2CreateButton::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_bCollCheck) {
		_int iCost = CResourceMgr::GetInstance()->Get_Build_Cost(BUILDTYPE::TRAP2);
		if (iCost == -1) {
			m_bCollCheck = false;
			return 0;
		}

		if (CResourceMgr::GetInstance()->Get_Money() - iCost >= 0) {
				static_cast<CBuildCreateBoard*>(m_pConUI)
					->Set_BuildType(BUILDTYPE::TRAP2);
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
			->Get_BuildType() != BUILDTYPE::TRAP2)
		{
			m_pBuildMap->Delete_PreView();
			m_bPick_Check = false;
		}

		m_pBuildMap->Show_PreView(BUILDTYPE::TRAP2);
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CTrap2CreateButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CTrap2CreateButton::Render_GameObject()
{
	CUIImage::Render_GameObject();

	_vec2 vPos2 = { 500.f, 535.f };
	_tchar srTest[100] = {};
	swprintf_s(srTest, L"³ª¹«Æ®·¦");
	Engine::Render_Font(L"Font_ResourceUI3", srTest, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

HRESULT CTrap2CreateButton::Add_Component()
{

	return S_OK;
}

CTrap2CreateButton* CTrap2CreateButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI)
{
	CTrap2CreateButton* pInstance = new CTrap2CreateButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pUI))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTrap2CreateButton::Free()
{
	m_pBuildMap->Delete_PreView();
	CUIImage::Free();
}
