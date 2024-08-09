#include "stdafx.h"
#include "..\Header\BossHP.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "ResourceMgr.h"

CBossHP::CBossHP(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUIImage(pGraphicDev)
{
}

CBossHP::CBossHP(const CBossHP& rhs)
	: CUIImage(rhs)
{
}

CBossHP::~CBossHP()
{
}

HRESULT CBossHP::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CUI::Setting_UI(L"Proto_BossHP"), E_FAIL);
	FAILED_CHECK_RETURN(CUIImage::Ready_GameObject(), E_FAIL);

	m_iTextureNum = 0;

	return S_OK;
}

_int CBossHP::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (Start_Point == _vec3(0.f, 0.f, 0.f)) {
			Start_Point = (*m_vTransform->Get_Pos()) - (m_vTransform->m_vScale);
	}
	else {
		Cut_HP();
	}

	return CUIImage::Update_GameObject(fTimeDelta);
}

void CBossHP::LateUpdate_GameObject()
{
	CUIImage::LateUpdate_GameObject();
}

void CBossHP::Cut_HP()
{

	if (m_vTransform->m_vInfo[INFO_POS].x <= Start_Point.x)
		return;

	vector<CGameObject*> vecMonsters = Engine::CManagement::GetInstance()->Get_GameLogic_Objects(OBJECTTYPE::MONSTER);
	CCharacter* pBoss = nullptr;

	for (auto& iter : vecMonsters) {
		if (static_cast<CCharacter*>(iter)->Get_MonsterType() == MOSTERID::RICH) {
			pBoss = static_cast<CCharacter*>(iter);
		}
	}

	if (pBoss == nullptr || pBoss->Get_Dead())
		return;

	_float iMaxHP = (pBoss)->Get_MaxHP();
	_float iCurHP = (pBoss)->Get_HP();

	if (iMaxHP < 0 || iCurHP < 0)
		return;

	_float fRatio = 200.f * (iCurHP / iMaxHP);

	m_vTransform->m_vScale.x = fRatio;

	m_vTransform->m_vInfo[INFO_POS].x = Start_Point.x + m_vTransform->m_vScale.x;
}

void CBossHP::Render_GameObject()
{

	CUIImage::Render_GameObject();

}

HRESULT CBossHP::Add_Component()
{

	return S_OK;
}

CBossHP* CBossHP::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBossHP* pInstance = new CBossHP(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);

		MSG_BOX("ResourceBox Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBossHP::Free()
{
	CUIImage::Free();
}
