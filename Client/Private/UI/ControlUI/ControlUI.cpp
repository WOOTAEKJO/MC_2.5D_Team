#include "stdafx.h"
#include "..\Header\ControlUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "UIImage.h"

CControlUI::CControlUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
}

CControlUI::CControlUI(const CControlUI& rhs)
	: CUI(rhs)
{
}

CControlUI::~CControlUI()
{
}


HRESULT CControlUI::Ready_GameObject()
{

	FAILED_CHECK_RETURN(CUI::Ready_GameObject(), E_FAIL);

	return S_OK;
}

_int CControlUI::Update_GameObject(const _float& fTimeDelta)
{
	if (!m_vecItemImage.empty()) {
		_bool bCheck = true;
		for (auto& iter : m_vecItemImage) {
			iter->Update_GameObject(fTimeDelta);
			if (static_cast<CUI*>(iter)->Get_HideCheck() == true) {
				m_bHide = true;
			}

			if (m_bHide == true) {
				if (static_cast<CUI*>(iter)->Get_HideCheck() == true) {
					bCheck = false;
				}

				if (bCheck && iter == m_vecItemImage.back()) {
					m_bHide = false;
					//Set_Dead();
				}
				
			}
		}
	}

	return CUI::Update_GameObject(fTimeDelta);
}

void CControlUI::LateUpdate_GameObject()
{
	if (!m_vecItemImage.empty()) {
		for (auto& iter : m_vecItemImage) {
			iter->LateUpdate_GameObject();
		}
	}

	CUI::LateUpdate_GameObject();
}

void CControlUI::Render_GameObject()
{
	CUI::Render_GameObject();

	if (!m_bHide) {
		if (!m_vecItemImage.empty()) {
			for (auto& iter : m_vecItemImage) {
				iter->Render_GameObject();
			}
		}
	}
}

void CControlUI::Delete_ItemImage()
{
	if (!m_vecItemImage.empty()) {
		for_each(m_vecItemImage.begin(), m_vecItemImage.end(), CDeleteObj());
		m_vecItemImage.clear();
	}
}

void CControlUI::Mouse_Picking(_vec3* vPos)
{
	
	POINT	ptMouse{};
	
	GetCursorPos(&ptMouse);
	
	ScreenToClient(g_hWnd, &ptMouse);
	
	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	
	m_pGraphicDev->GetViewport(&ViewPort);
	
	vPos->x = ptMouse.x - (ViewPort.Width * 0.5f);
	vPos->y = -(ptMouse.y - (ViewPort.Height * 0.5f));
	vPos->z = 1.f;
	

}

_bool CControlUI::Pick_UI()
{
	if (m_vecItemImage.empty())
		return false;

	if (Engine::Mouse_Down(DIM_LB)) {
		_vec3 vPickPos,vUIPos,vUIScale;
		Mouse_Picking(&vPickPos);

		for (_int i = 0; i < m_vecItemImage.size(); i++) {

			if (m_vecItemImage[i] == nullptr)
				return false;

			vUIPos = *m_vecItemImage[i]->Get_Transform()->Get_Pos();
			vUIScale = *m_vecItemImage[i]->Get_Transform()->Get_Scale();

			if ((vUIPos.x - (vUIScale.x )) <= vPickPos.x && vPickPos.x <= (vUIPos.x + (vUIScale.x ))
				&&
				(vUIPos.y - (vUIScale.y )) <= vPickPos.y && vPickPos.y <= (vUIPos.y + (vUIScale.y ))) {

				dynamic_cast<CUIImage*>(m_vecItemImage[i])->Set_CollCheck();

				return true;
			}
		}
	}

	return false;
}

void CControlUI::Free()
{


	for_each(m_vecItemImage.begin(), m_vecItemImage.end(), CDeleteObj());
	m_vecItemImage.clear();

	CUI::Free();
}

HRESULT CControlUI::Add_Component()
{

	return S_OK;
}
