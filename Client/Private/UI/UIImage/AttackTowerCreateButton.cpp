#include "stdafx.h"
#include "..\Header\AttackTowerCreateButton.h"

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

CAttackTowerCreateButton::CAttackTowerCreateButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CAttackTowerCreateButton::CAttackTowerCreateButton(const CAttackTowerCreateButton& rhs)
	: CUIImage(rhs)
{
}

CAttackTowerCreateButton::~CAttackTowerCreateButton()
{
}

HRESULT CAttackTowerCreateButton::Ready_GameObject(CUI* pUI)
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_AttackTowerImage"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	m_pBuildMap = dynamic_cast<CBuildMap*>(Engine::CManagement::GetInstance()
		->Get_Environment_Objects(OBJECTTYPE::BUILDMAP).front());
	NULL_CHECK(m_pBuildMap);

	m_pConUI = pUI;

	return S_OK;
}

_int CAttackTowerCreateButton::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_bCollCheck) {
		_int iCost = CResourceMgr::GetInstance()->Get_Build_Cost(BUILDTYPE::ATTACKTOWER);
		if (iCost == -1) {
			m_bCollCheck = false;
			return 0;
		}

		if (CResourceMgr::GetInstance()->Get_Money() - iCost >= 0) {
			static_cast<CBuildCreateBoard*>(m_pConUI)
				->Set_BuildType(BUILDTYPE::ATTACKTOWER);
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
			->Get_BuildType() != BUILDTYPE::ATTACKTOWER)
		{
			m_pBuildMap->Delete_PreView();
			m_bPick_Check = false;
		}

		m_pBuildMap->Show_PreView(BUILDTYPE::ATTACKTOWER);
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CAttackTowerCreateButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CAttackTowerCreateButton::Render_GameObject()
{
	CUIImage::Render_GameObject();

	_vec2 vPos2 = { 110.f, 535.f };
	_tchar srTest[100] = {};
	swprintf_s(srTest, L"공격타워");
	Engine::Render_Font(L"Font_ResourceUI3", srTest, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

HRESULT CAttackTowerCreateButton::Add_Component()
{

	return S_OK;
}

CAttackTowerCreateButton* CAttackTowerCreateButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, CUI* pUI)
{
	CAttackTowerCreateButton* pInstance = new CAttackTowerCreateButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(pUI))) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CAttackTowerCreateButton::Free()
{
	m_pBuildMap->Delete_PreView();
	CUIImage::Free();
}
