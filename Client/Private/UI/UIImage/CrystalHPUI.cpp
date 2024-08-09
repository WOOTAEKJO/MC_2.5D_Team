#include "stdafx.h"
#include "..\Header\CrystalHPUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

CCrystalHPUI::CCrystalHPUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
	//D3DXMatrixIdentity(&m_matWorld);
}

CCrystalHPUI::CCrystalHPUI(const CCrystalHPUI& rhs)
	: CUIImage(rhs)
{
}

CCrystalHPUI::~CCrystalHPUI()
{
}

HRESULT CCrystalHPUI::Ready_GameObject()
{
	//FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BossHP"), E_FAIL);
	FAILED_CHECK_RETURN(CCrystalHPUI::Add_Component(), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_vTransform->Set_Scale(50.f, 7.f, 20.f);

	m_iTextureNum = 0;
	//m_eUI_RenderType = UIORDER::HPUI;
	Set_UI_RenderType(UIORDER::HPUI);
	return S_OK;
}

_int CCrystalHPUI::Update_GameObject(const _float& fTimeDelta)
{
	//Add_Count(fTimeDelta);
	if (m_pTarget == nullptr || m_pTarget->Get_Dead()) {
		Set_Dead();
		return 0;
	}

	Cal_Pos();
	
	Cut_HP();
	
	return CUIImage::Update_GameObject(fTimeDelta);
}

void CCrystalHPUI::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CCrystalHPUI::Cut_HP()
{

	/*if (m_vTransform->m_vInfo[INFO_POS].x <= Start_Point.x)
		return;*/

	if (m_pTarget == nullptr || m_pTarget->Get_Dead())
		return;

	CCharacter* pCrystal = static_cast<CCharacter*>(m_pTarget);

	_float iMaxHP = pCrystal->Get_MaxHP();
	_float iCurHP = pCrystal->Get_HP();

	if (iMaxHP < 0 || iCurHP < 0)
		return;
	
	_float fRatio = 70.f * (iCurHP / iMaxHP);

	m_vTransform->m_vScale.x = fRatio;

	//Cal_Pos();

	m_vTransform->m_vInfo[INFO_POS].x = Start_Point.x;// + m_vTransform->m_vScale.x;

}

void CCrystalHPUI::Cal_Pos()
{
	if (Get_Dead())
		return ;

	_matrix matWorld,matView, matProj;

	if (m_pTarget == nullptr || m_pTarget->Get_Dead())
		return ;

	_vec3 vWindwPos = *m_pTarget->Get_Transform()->Get_Pos();
	//vWindwPos.x -= 10.f;
	//vWindwPos.z += 10.f;
	vWindwPos.y += 7.f;

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
	vWindwPos.x -= 70.f;//m_vTransform->m_vScale.x;
	m_vTransform->m_vInfo[INFO_POS] = vWindwPos;
	Start_Point = *m_vTransform->Get_Pos();// -((m_vTransform->m_vScale));
}

void CCrystalHPUI::Render_GameObject()
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
	m_bHide = true;
}

HRESULT CCrystalHPUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pLBufferCom = dynamic_cast<CRcTexLeft*>(Clone_Proto(L"Proto_RcTexLeft"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_LBuffer", pComponent });
	
	pComponent = m_vTransform = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_BossHP"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

CCrystalHPUI* CCrystalHPUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCrystalHPUI* pInstance = new CCrystalHPUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCrystalHPUI::Free()
{
	CUIImage::Free();
}
