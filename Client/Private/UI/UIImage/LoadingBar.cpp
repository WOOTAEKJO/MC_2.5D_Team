#include "stdafx.h"
#include "..\Header\LoadingBar.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

CLoadingBar::CLoadingBar(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CLoadingBar::CLoadingBar(const CLoadingBar& rhs)
	: CUIImage(rhs)
{
}

CLoadingBar::~CLoadingBar()
{
}

HRESULT CLoadingBar::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CLoadingBar::Add_Component(), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_vTransform->Set_Scale(50.f, 7.f, 20.f);

	m_iTextureNum = 0;
	//m_eUI_RenderType = UIORDER::HPUI;
	Set_UI_RenderType(UIORDER::HPUI);
	return S_OK;
}

_int CLoadingBar::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CLoadingBar::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CLoadingBar::Cal()
{
	if (m_pOwner == nullptr || m_pOwner->Get_Dead())
		return;

	CCharacter* pCrystal = static_cast<CCharacter*>(m_pOwner);

	_float iMaxHP = pCrystal->Get_MaxHP();
	_float iCurHP = pCrystal->Get_HP();

	if (iMaxHP < 0 || iCurHP < 0)
		return;

	_float fRatio = 70.f * (iCurHP / iMaxHP);

	m_vTransform->m_vScale.x = fRatio;

	//Cal_Pos();

	//m_vTransform->m_vInfo[INFO_POS].x = Start_Point.x;
}

void CLoadingBar::Render_GameObject()
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
		m_pLBufferCom->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
		m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
	}

}

HRESULT CLoadingBar::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pLBufferCom = dynamic_cast<CRcTexLeft*>(Clone_Proto(L"Proto_RcTexLeft"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_LBuffer", pComponent });

	pComponent = m_vTransform = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_LoadingBar"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

CLoadingBar* CLoadingBar::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLoadingBar* pInstance = new CLoadingBar(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLoadingBar::Free()
{
	CUIImage::Free();
}
