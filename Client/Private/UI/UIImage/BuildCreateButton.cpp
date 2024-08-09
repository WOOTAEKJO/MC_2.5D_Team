#include "stdafx.h"
#include "..\Header\BuildCreateButton.h"

#include "Export_System.h"
#include "Export_Utility.h"
#include "ObjCreationMgr.h"

#include "Store.h"

#include "BowSoldier.h"

CBuildCreateButton::CBuildCreateButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CBuildCreateButton::CBuildCreateButton(const CBuildCreateButton& rhs)
	: CUIImage(rhs)
{
}

CBuildCreateButton::~CBuildCreateButton()
{
}

HRESULT CBuildCreateButton::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_NonButton"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	return S_OK;
}

_int CBuildCreateButton::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_bCollCheck) {

		

		m_iTextureNum = 1;
		m_fCount = 0.f;
		m_bCollCheck = false;
	}

	if (m_iTextureNum == 1) {
		if (m_fCount > 0.1f) {
			m_iTextureNum = 0;
			m_fCount = 0.f;
		}
	}

	

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CBuildCreateButton::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CBuildCreateButton::Render_GameObject()
{
	CUIImage::Render_GameObject();

	if (!m_bHide) {
		_vec3 vPos = *m_vTransform->Get_Pos();
		_vec3 vScale = *m_vTransform->Get_Scale();
		_vec2 vPos2 = { vPos.x + (vScale.x * 1.4f)  ,vPos.y - (vScale.y * 0.5f) };
		_tchar srTest[100] = {};
		swprintf_s(srTest, L"»ý¼º");
		Engine::Render_Font(L"Font_UI", srTest, &vPos2, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	}
}

HRESULT CBuildCreateButton::Add_Component()
{

	return S_OK;
}

CBuildCreateButton* CBuildCreateButton::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBuildCreateButton* pInstance = new CBuildCreateButton(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBuildCreateButton::Free()
{
	CUIImage::Free();
}
