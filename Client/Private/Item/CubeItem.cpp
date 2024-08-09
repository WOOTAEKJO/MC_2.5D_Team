#include "stdafx.h"
#include "..\Header\CubeItem.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ImGuiMgr.h"

#include "SaveLoadMgr.h"

CCubeItem::CCubeItem(LPDIRECT3DDEVICE9 pGraphicDev)
	:CDamageableObject(pGraphicDev), m_eWeaponType(WEAPONTYPE::WEAPON_END)
{
	_matrix matdd;
	//D3DXMatrixIdentity(&matdd);

	pGraphicDev->GetTransform(D3DTS_VIEW, &matdd);

}

CCubeItem::CCubeItem(const CCubeItem& rhs)
	:CDamageableObject(rhs)
{
}

CCubeItem::~CCubeItem()
{
}

HRESULT CCubeItem::Ready_GameObject()
{
	//m_bRender = true;
	return S_OK;
}

_int CCubeItem::Update_GameObject(const _float& fTimeDelta)
{
	if (!m_vecTransCom.empty()) {
		for (_uint i = 0; i < m_vecTransCom.size(); i++) {
			m_vecTransCom[i]->m_matParWorld = m_vTransform->m_matWorld;
		} // 파츠들의 부모 행렬은 중심의 행렬;
	}
	
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	
	Render_Reset();
	
	return __super::Update_GameObject(fTimeDelta);
}

void CCubeItem::LateUpdate_GameObject()
{
	__super::LateUpdate_GameObject();
}

void CCubeItem::Render_GameObject()
{
	if (!m_bRender) return;

	/*m_pGraphicDev->SetTransform(D3DTS_WORLD, m_vTransform->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_vecTextureCom[0]->Render_Textrue(0);
	m_vecBufferCom[0]->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);*/

	D3DMATERIAL9			tMtrl;
	ZeroMemory(&tMtrl, sizeof(D3DMATERIAL9));

	tMtrl.Diffuse = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Specular = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Ambient = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Emissive = { 0.f, 0.f, 0.f, 0.f };
	tMtrl.Power = 0.f;

	m_pGraphicDev->SetMaterial(&tMtrl);

	if (!m_vecTransCom.empty()) {
		for (_uint i = 0; i < m_vecTransCom.size(); i++) {
			m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);

			m_pGraphicDev->SetTransform(D3DTS_WORLD, m_vecTransCom[i]->Get_WorldMatrix());
			m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

			m_vecTextureCom[i]->Render_Textrue(m_vecItemParts[i]->iTextureNum);
			m_vecBufferCom[i]->Render_Buffer();

			m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
		}  // 파츠 큐브들 렌더

	}
}

HRESULT CCubeItem::Set_Item(const _tchar* tItemTag)
{
	FAILED_CHECK_RETURN(CCubeItem::Default_Component(*CSaveLoadMgr::GetInstance()->Get_ItemPartsInfoData(tItemTag)), E_FAIL);

	TOTALITEMINFO* pTemp = CSaveLoadMgr::GetInstance()->Get_ItmeTotalInfoData(tItemTag);
	m_pItemTotal = new TOTALITEMINFO;
	m_pItemTotal->vStartPosition = pTemp->vStartPosition;
	m_pItemTotal->vStartRotation  = pTemp->vStartRotation;
	m_pItemTotal->vScale  = pTemp->vScale;

	m_vTransform->Set_Pos(m_pItemTotal->vStartPosition );
	m_vTransform->Set_Scale(m_pItemTotal->vScale);
	m_vTransform->Set_Angle(D3DXToRadian(m_pItemTotal->vStartRotation));

	return S_OK;
}

HRESULT CCubeItem::Default_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	CComponent* pComponent = nullptr;

	/*pComponent = m_pBufferCom = dynamic_cast<CCubeTexItem*>(Engine::Clone_Proto(L"Proto_CubeTexItem"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer_TOTAL", pComponent });

	pComponent = m_vTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_TOTAL", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_139Texture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture_TOTAL", pComponent });*/

	pComponent = m_vTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform_TOTAL", pComponent });

	for (_uint i = 0; i < vecItemParts.size(); i++) {

		{
			TCHAR* szFileName = new TCHAR[256];
			CTransform* pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
			NULL_CHECK_RETURN(pTransform, E_FAIL);
			pTransform->m_vInfo[INFO_POS] = vecItemParts[i]->vPosition;
			wsprintf(szFileName, L"Com_Transform%d", i);
			m_mapComponent[ID_DYNAMIC].insert({ szFileName , pTransform });
			m_vecKey.push_back(szFileName);
			m_vecTransCom.push_back(pTransform);

		}

		{
			TCHAR* szFileName = new TCHAR[256];

			CCubeTexItem* pBuffer = dynamic_cast<CCubeTexItem*>(Engine::Clone_Proto(L"Proto_CubeTexItem"));
			NULL_CHECK_RETURN(pBuffer, E_FAIL);
			wsprintf(szFileName, L"Com_Buffer%d", i);
			m_mapComponent[ID_STATIC].insert({ szFileName , pBuffer });
			m_vecKey.push_back(szFileName);
			m_vecBufferCom.push_back(pBuffer);
		}

		{
			TCHAR* szFileName = new TCHAR[256];

			CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_ColorCubeTexture"));
			NULL_CHECK_RETURN(pTexture, E_FAIL);
			wsprintf(szFileName, L"Com_Texture%d", i);
			m_mapComponent[ID_STATIC].insert({ szFileName , pTexture });
			m_vecKey.push_back(szFileName);
			m_vecTextureCom.push_back(pTexture);

		}

		PARTSITEMINFO* pTemp = new PARTSITEMINFO;
		pTemp->iTextureNum = vecItemParts[i]->iTextureNum;
		pTemp->vPosition = vecItemParts[i]->vPosition;
		m_vecItemParts.push_back(pTemp);

	}

	return S_OK;
}

void CCubeItem::Free()
{
	for_each(m_vecKey.begin(), m_vecKey.end(), CDeleteArrayObj());
	m_vecKey.clear();

	/*for_each(m_vecTransCom.begin(), m_vecTransCom.end(), CDeleteObj());
	m_vecTransCom.clear();

	for_each(m_vecTextureCom.begin(), m_vecTextureCom.end(), CDeleteObj());
	m_vecTextureCom.clear();

	for_each(m_vecBufferCom.begin(), m_vecBufferCom.end(), CDeleteObj());
	m_vecBufferCom.clear();*/

	
	for_each(m_vecItemParts.begin(), m_vecItemParts.end(), CDeleteObj2());
	m_vecItemParts.clear();

	Safe_Delete(m_pItemTotal);
	
	__super::Free();
}
