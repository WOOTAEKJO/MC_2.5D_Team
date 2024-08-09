#include "stdafx.h"
#include "..\Header\RichLaser.h"
#include "SoundMgr.h"
#include "Export_Utility.h"


CRichLaser::CRichLaser(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEffect(pGraphicDev)
{
}
CRichLaser::CRichLaser(const CRichLaser& rhs)
	: CEffect(rhs)
{

}

CRichLaser::~CRichLaser()
{
}

HRESULT CRichLaser::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//CSoundManager::GetInstance()->StopSound(CHANNELID::SOUND_EFFECT);
	//CSoundManager::GetInstance()->PlaySound(L"explode1.mp3", CHANNELID::SOUND_EFFECT, 0.5f);

	return S_OK;
}

_int CRichLaser::Update_GameObject(const _float& fTimeDelta)
{
	

	Animation_Frame(fTimeDelta);

	
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return __super::Update_GameObject(fTimeDelta);
}

void CRichLaser::LateUpdate_GameObject()
{
	_vec3	vPos;
	m_vTransform->Get_Info(INFO_POS, &vPos);

	__super::Compute_ViewZ(&vPos);
}

CRichLaser* CRichLaser::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRichLaser* pInstance = new CRichLaser(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRichLaser::Render_GameObject()
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
	m_pEffectBufferCom->Render_Buffer();

	//m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}



void CRichLaser::Animation_Frame(const _float& fTimeDelta)
{
	if (60.f > m_fCount) {

		if (m_fFrame >= 28.f) {
			Set_Dead();
			m_bCheck = true;
		}
		else {
			m_fFrame++;
		}
		m_fCount = 0.f;
	}
	else {
		m_fCount += fTimeDelta;
	}
}

HRESULT CRichLaser::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pEffectBufferCom = dynamic_cast<CRcEffectTex*>(Engine::Clone_Proto(L"Proto_RcEffectTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_EffectBuffer", pComponent });

	pComponent = m_vTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_RichLaser"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

void CRichLaser::Free()
{
	__super::Free();
}
