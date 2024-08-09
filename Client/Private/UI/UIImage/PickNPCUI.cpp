#include "stdafx.h"
#include "..\Header\PickNPCUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

CPickNPCUI::CPickNPCUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CPickNPCUI::CPickNPCUI(const CPickNPCUI& rhs)
	: CUIImage(rhs)
{
}

CPickNPCUI::~CPickNPCUI()
{
}

HRESULT CPickNPCUI::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_PickNPC"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	//m_iTextureNum = 0;

	m_vTransform->Set_Scale(10.f, 10.f, 1.f);
	//m_eUI_RenderType = UIORDER::OBJECTUI;
	Set_UI_RenderType(UIORDER::OBJECTUI);
	return S_OK;
}

_int CPickNPCUI::Update_GameObject(const _float& fTimeDelta)
{
	Cal_Pos();

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CPickNPCUI::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CPickNPCUI::Cal_Pos()
{
	if (Get_Dead())
		return;

	if (m_pTarget == nullptr || m_pTarget->Get_Dead())
		return;

	_vec3 vWindwPos = *m_pTarget->Get_Transform()->Get_Pos();

	vWindwPos.y += 2.5f;

	_matrix matWorld, matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	//D3DXVec3TransformCoord(&vWindwPos, &vWindwPos, &matWorld);
	D3DXVec3TransformCoord(&vWindwPos, &vWindwPos, &matView);
	D3DXVec3TransformCoord(&vWindwPos, &vWindwPos, &matProj);


	vWindwPos.x *= WINCX * 0.5f;
	vWindwPos.y *= WINCY * 0.5f;
	/*
	-1,1 = 0 0
	1, -1 = 800 600
	x/2 = i/800;
	400 * x = i;
	*/
	//vWindwPos.x -= m_vTransform->m_vScale.x;
	m_vTransform->m_vInfo[INFO_POS] = vWindwPos;
}

void CPickNPCUI::Render_GameObject()
{

	//CUIImage::Render_GameObject();

	if (!m_bHide) {
		_matrix matView, matProj;
		m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
		m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_vTransform->Get_WorldMatrix());
		m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matUIView);
		m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matUIProj);

		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		m_pTextureCom->Render_Textrue(m_iTextureNum);
		m_pBufferCom->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
		m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
	}
	m_bHide = true;
}

HRESULT CPickNPCUI::Add_Component()
{

	return S_OK;
}

CPickNPCUI* CPickNPCUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPickNPCUI* pInstance = new CPickNPCUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPickNPCUI::Free()
{
	CUIImage::Free();
}
