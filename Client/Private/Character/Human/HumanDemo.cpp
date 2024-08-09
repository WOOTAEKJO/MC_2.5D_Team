#include "stdafx.h"
#include "..\Header\HumanDemo.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "HumanAnimation.h"

CHumanDemo::CHumanDemo(LPDIRECT3DDEVICE9 pGraphicDev)
	:CHuman(pGraphicDev), m_pDemo(nullptr)
{
}

CHumanDemo::CHumanDemo(const CHumanDemo& rhs)
	:CHuman(rhs), m_pDemo(rhs.m_pDemo)
{
}

CHumanDemo::~CHumanDemo()
{
}

HRESULT CHumanDemo::Ready_GameObject()
{
	FAILED_CHECK_RETURN(CHuman::SetUp_Parts(
		L"Proto_PlayerHeadTexture"
		, L"Proto_PlayerBodyTexture"
		, L"Proto_PlayerArm1Texture"
		, L"Proto_PlayerArm2Texture"
		, L"Proto_PlayerLeg1Texture"
		, L"Proto_PlayerLeg2Texture"), E_FAIL);
	FAILED_CHECK_RETURN(CHuman::Default_Ratio(), E_FAIL);

	m_pDemo = CHumanAnimation::Create(this, L"IDLE");
	FAILED_CHECK_RETURN(Add_State(), E_FAIL);

	m_iHP = 100;

	return S_OK;
}

_int CHumanDemo::Update_GameObject(const _float& fTimeDelta)
{
	
	m_pDemo->Update_Animation(this, fTimeDelta);

	return CHuman::Update_GameObject(fTimeDelta);
}

void CHumanDemo::LateUpdate_GameObject()
{

	//CHuman::Height_On_Terrain(false);
	CHuman::LateUpdate_GameObject();
}

void CHumanDemo::Render_GameObject()
{
	CHuman::Render_GameObject();
}

HRESULT CHumanDemo::Add_State()
{
	m_pDemo->Add_State(L"IDLE");

	return S_OK;
}

CHumanDemo* CHumanDemo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHumanDemo* pInstance = new CHumanDemo(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CHumanDemo::Free()
{
	m_pDemo->Free(this);
	Safe_Delete(m_pDemo);
	CHuman::Free();
}

