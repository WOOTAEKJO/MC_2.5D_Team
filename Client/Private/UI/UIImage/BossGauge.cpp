#include "stdafx.h"
#include "..\Header\BossGauge.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

#include "Rich.h"

CBossGauge::CBossGauge(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CBossGauge::CBossGauge(const CBossGauge& rhs)
	: CUIImage(rhs)
{
}

CBossGauge::~CBossGauge()
{
}

HRESULT CBossGauge::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BossGauge"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	return S_OK;
}

_int CBossGauge::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_fCount > 0.1f) {
		Fill_Gauge();
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CBossGauge::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CBossGauge::Fill_Gauge()
{
	/*if (m_vTransform->m_vInfo[INFO_POS].x + m_vTransform->m_vScale.x >= End_Point.x)
		return;*/

	vector<CGameObject*> vecMonsters = Engine::CManagement::GetInstance()->Get_GameLogic_Objects(OBJECTTYPE::MONSTER);
	CCharacter* pBoss = nullptr;

	for (auto& iter : vecMonsters) {
		if (static_cast<CCharacter*>(iter)->Get_MonsterType() == MOSTERID::RICH) {
			pBoss = static_cast<CCharacter*>(iter);
		}
	}

	if (pBoss == nullptr || pBoss->Get_Dead())
		return;

	_int iNum = static_cast<CRich*>(pBoss)->Get_GaugeCount();

	_float iRatio =  200.f / 2.f;

	_float iCurScale = iNum * iRatio;

	m_vTransform->m_vScale.x = iCurScale;

	m_vTransform->m_vInfo[INFO_POS].x = Start_Point.x + m_vTransform->m_vScale.x;
}

void CBossGauge::Render_GameObject()
{
	CUIImage::Render_GameObject();
}

HRESULT CBossGauge::Add_Component()
{

	return S_OK;
}

CBossGauge* CBossGauge::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBossGauge* pInstance = new CBossGauge(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBossGauge::Free()
{
	CUIImage::Free();
}
