#include "stdafx.h"
#include "..\Header\Flagpole.h"

#include "Export_System.h"
#include "Export_Utility.h"


CFlagpole::CFlagpole(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCubeItem(pGraphicDev)
{
	
}

CFlagpole::CFlagpole(const CFlagpole& rhs)
	: CCubeItem(rhs)
{
}

CFlagpole::~CFlagpole()
{
}

HRESULT CFlagpole::Add_Component(vector<PARTSITEMINFO*>& vecItemParts)
{
	return S_OK;
}


void CFlagpole::Free()
{
	CCubeItem::Free();
}


HRESULT CFlagpole::Ready_GameObject()
{
	CCubeItem::Ready_GameObject();
	return S_OK;
}

_int CFlagpole::Update_GameObject(const _float& fTimeDelta)
{
	_int result = CCubeItem::Update_GameObject(fTimeDelta);
	return result;
}

void CFlagpole::LateUpdate_GameObject()
{
	CCubeItem::LateUpdate_GameObject();
}

void CFlagpole::Render_GameObject()
{
	CCubeItem::Render_GameObject();
}

