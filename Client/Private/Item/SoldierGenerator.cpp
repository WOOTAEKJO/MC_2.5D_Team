#include "stdafx.h"
#include "..\Header\SoldierGenerator.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "ObjCreationMgr.h"
#include "SaveLoadMgr.h"

#include "SSoldier.h"

CSoldierGenerator::CSoldierGenerator(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCubeItem(pGraphicDev)
{
}

CSoldierGenerator::CSoldierGenerator(const CSoldierGenerator& rhs)
	: CCubeItem(rhs)
{
}

CSoldierGenerator::~CSoldierGenerator()
{
}

HRESULT CSoldierGenerator::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CCubeItem::Default_Component(*CSaveLoadMgr::GetInstance()->Get_ItemPartsInfoData(L"GENERATION")), E_FAIL);

	m_iHP = 100.f;

	return S_OK;
}

_int CSoldierGenerator::Update_GameObject(const _float& fTimeDelta)
{
	Add_Count(fTimeDelta);

	if (m_fTime > 6.f) {

		CObjCreationMgr::GetInstance()->Create<CSSoldier>(OBJECTTYPE::PLAYER, _vec3(12.f, 5.f, 12.f), _vec3(70.f, 5.f, 40.f));

		m_fTime = 0.f;
	}

	return CCubeItem::Update_GameObject(fTimeDelta);
}

void CSoldierGenerator::LateUpdate_GameObject()
{
	CCubeItem::LateUpdate_GameObject();
}

void CSoldierGenerator::Render_GameObject()
{
	CCubeItem::Render_GameObject();
}

HRESULT CSoldierGenerator::Add_Component()
{
	return S_OK;
}

CSoldierGenerator* CSoldierGenerator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSoldierGenerator* pInstance = new CSoldierGenerator(pGraphicDev);
	if (FAILED(pInstance->Ready_GameObject())) {
		Safe_Release(pInstance);
		MSG_BOX("Generator Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSoldierGenerator::Free()
{
	CCubeItem::Free();
}
