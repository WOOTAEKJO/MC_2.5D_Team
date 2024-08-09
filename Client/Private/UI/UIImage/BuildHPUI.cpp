#include "stdafx.h"
#include "..\Header\BuildHPUI.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

CBuildHPUI::CBuildHPUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
	//D3DXMatrixIdentity(&m_matWorld);
}

CBuildHPUI::CBuildHPUI(const CBuildHPUI& rhs)
	: CUIImage(rhs)
{
}

CBuildHPUI::~CBuildHPUI()
{
}

HRESULT CBuildHPUI::Ready_GameObject()
{
	//FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BossHP"), E_FAIL);
	FAILED_CHECK_RETURN(CBuildHPUI::Add_Component(), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_vTransform->Set_Scale(50.f, 7.f, 20.f);
	
	m_iTextureNum = 0;
	//m_eUI_RenderType = UIORDER::HPUI;
	Set_UI_RenderType(UIORDER::HPUI);
	return S_OK;
}

_int CBuildHPUI::Update_GameObject(const _float& fTimeDelta)
{
	//Add_Count(fTimeDelta);

	if (m_pOwner == nullptr || m_pOwner->Get_Dead()) {
		Set_Dead();
		return 0;
	}

	if (m_pOwner != nullptr) {
		if (m_pOwner->Get_ObjectType() == OBJECTTYPE::ALLY_BUILDING) {
			m_iTextureNum = 1;
		}
		else if(m_pOwner->Get_ObjectType() == OBJECTTYPE::MONSTER_BUILDING){
			m_iTextureNum = 0;
		}

	}

	Cal_Pos();

	Cut_HP();

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CBuildHPUI::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CBuildHPUI::Cut_HP()
{

	/*if (m_vTransform->m_vInfo[INFO_POS].x <= Start_Point.x)
		return;*/

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

	m_vTransform->m_vInfo[INFO_POS].x = Start_Point.x;// + m_vTransform->m_vScale.x;

}

void CBuildHPUI::Cal_Pos()
{
	if (Get_Dead())
		return;

	_matrix matWorld, matView, matProj;

	if (m_pOwner == nullptr || m_pOwner->Get_Dead())
		return;

	_vec3 vWindwPos = *m_pOwner->Get_Transform()->Get_Pos();

	if (vWindwPos == nullptr)
		return;

	//vWindwPos.x -= 10.f;
	//vWindwPos.z += 10.f;
	vWindwPos.y += 15.f;

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

void CBuildHPUI::Render_GameObject()
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

HRESULT CBuildHPUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pLBufferCom = dynamic_cast<CRcTexLeft*>(Clone_Proto(L"Proto_RcTexLeft"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_LBuffer", pComponent });

	pComponent = m_vTransform = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_BuildHPUI"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

CBuildHPUI* CBuildHPUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBuildHPUI* pInstance = new CBuildHPUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBuildHPUI::Free()
{
	CUIImage::Free();
}
