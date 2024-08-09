#include "stdafx.h"
#include "..\Header\MouseUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

CMouseUI::CMouseUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CMouseUI::CMouseUI(const CMouseUI& rhs)
	: CUIImage(rhs)
{
}

CMouseUI::~CMouseUI()
{
}

HRESULT CMouseUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_MouseUI"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	//m_vTransform->m_vAngle.z = D3DXToRadian(45.f);
	m_vTransform->Set_Scale(_vec3(20.f, 20.f, 1.f));
	//m_vTransform->Set_Pos(_vec3(20.f,20.f, 20.f));
	Set_UI_RenderType(UIORDER::MOUSERUI);
	ShowCursor(false);
	return S_OK;
}

_int CMouseUI::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	Mouse_Pos_Cal();

	if (Engine::Mouse_Pressing(DIM_LB) || Engine::Mouse_Pressing(DIM_RB)) {
		m_iTextureNum = 1;
	}
	else {
		m_iTextureNum = 0;
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CMouseUI::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CMouseUI::Mouse_Pos_Cal()
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	

	_vec3 vMouse = { (_float)ptMouse.x,-(_float)ptMouse.y,1.f };

	
	vMouse.x -= 400.f;
	vMouse.y += 295.f;

	m_vTransform->m_vInfo[INFO_POS] = vMouse;
}

void CMouseUI::Render_GameObject()
{

	CUIImage::Render_GameObject();

}

HRESULT CMouseUI::Add_Component()
{

	return S_OK;
}

CMouseUI* CMouseUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMouseUI* pInstance = new CMouseUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CMouseUI::Free()
{
	CUIImage::Free();
}
