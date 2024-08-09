#include "stdafx.h"
#include "..\Header\UI.h"

#include "Export_Utility.h"
#include "Export_System.h"

CUI::CUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CUI::CUI(const CUI& rhs)
	:CGameObject(rhs)
{
}

CUI::~CUI()
{
}

HRESULT CUI::Ready_GameObject()
{

	D3DXMatrixIdentity(&m_matUIView);
	D3DXMatrixOrthoLH(&m_matUIProj, WINCX, WINCY, 0.0f, 100.0f);

	/*m_fX = m_fSizeX * 0.5f;
	m_fY = m_fSizeY * 0.5f;

	m_pTransformCom->m_vScale.x = m_fSizeX * 0.5f;
	m_pTransformCom->m_vScale.y = m_fSizeY * 0.5f;

	m_pTransformCom->m_vInfo[INFO_POS].x = m_fX - WINCX * 0.5f;
	m_pTransformCom->m_vInfo[INFO_POS].y = -m_fY + WINCY * 0.5f;*/

	return S_OK;
}

_int CUI::Update_GameObject(const _float& fTimeDelta)
{

	/*if (m_iKeyCount % 2 == 1)
		m_bButtonPress = true;
	else
		m_bButtonPress = false;*/

	Engine::Add_RenderGroup(RENDER_UI, this);

	return CGameObject::Update_GameObject(fTimeDelta);
}

void CUI::LateUpdate_GameObject()
{
	/*_vec3	vPos;
	m_vTransform->Get_Info(INFO_POS, &vPos);

	__super::Compute_ViewZ(&vPos);*/
	CGameObject::LateUpdate_GameObject();
}

void CUI::Render_GameObject()
{
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
}

HRESULT CUI::Add_Component()
{
	
	return S_OK;
}

HRESULT CUI::Setting_UI(const _tchar* tTextureTag)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_vTransform = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(tTextureTag));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	/*for (int i = 0; i < ID_END; ++i)
		for (auto& iter : m_mapComponent[i])
			iter.second->Init_Component(this);*/

	return S_OK;
}

void CUI::Free()
{
	Safe_Delete(m_pUIState);

	__super::Free();
}
