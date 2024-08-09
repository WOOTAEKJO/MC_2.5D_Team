#include "stdafx.h"
#include "..\Header\RichAttackRange.h"
#include "SoundMgr.h"
#include "Export_Utility.h"

#include "Rich.h"

CRichAttackRange::CRichAttackRange(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEffect(pGraphicDev)
{
}
CRichAttackRange::CRichAttackRange(const CRichAttackRange& rhs)
	: CEffect(rhs)
{

}

CRichAttackRange::~CRichAttackRange()
{
}

HRESULT CRichAttackRange::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//CSoundManager::GetInstance()->StopSound(CHANNELID::SOUND_EFFECT);
	//CSoundManager::GetInstance()->PlaySound(L"explode1.mp3", CHANNELID::SOUND_EFFECT, 0.5f);

	return S_OK;
}

_int CRichAttackRange::Update_GameObject(const _float& fTimeDelta)
{
	if (m_OwnerTransform != nullptr) {
		if (((m_OwnerTransform->Get_Scale()->x) * 8.f) >= m_vTransform->m_vScale.x) {
			m_fCount += fTimeDelta;
			if (m_fCount > 0.15f) {
				m_vTransform->m_vScale *= 1.05f;
				m_fCount = 0.f;
			}
		}
	}

	_matrix		matWorld, matView, matBill;

	matWorld = *m_vTransform->Get_WorldMatrix();

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixIdentity(&matBill);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	// 주의 사항

	// 빌(자전의 역행렬) * 월드(스 * 자 * 이)

	m_vTransform->Set_WorldMatrix(&(matBill * matWorld));


	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return __super::Update_GameObject(fTimeDelta);
}

void CRichAttackRange::LateUpdate_GameObject()
{
	_vec3	vPos;
	m_vTransform->Get_Info(INFO_POS, &vPos);

	__super::Compute_ViewZ(&vPos);
}

CRichAttackRange* CRichAttackRange::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRichAttackRange* pInstance = new CRichAttackRange(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichAttackRange::Render_GameObject()
{
	D3DMATERIAL9			tMtrl;
	ZeroMemory(&tMtrl, sizeof(D3DMATERIAL9));

	tMtrl.Diffuse = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Specular = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Ambient = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Emissive = { 0.f, 0.f, 0.f, 0.f };
	tMtrl.Power = 0.f;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_vTransform->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);

	m_pTextureCom->Render_Textrue(_ulong(m_fFrame));
	m_pBufferCom->Render_Buffer();

	//m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}



HRESULT CRichAttackRange::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_vTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_RichAttackRange"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

void CRichAttackRange::Free()
{
	__super::Free();
}
