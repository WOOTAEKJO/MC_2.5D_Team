#include "stdafx.h"
#include "..\Header\HNPC.h"

#include "Export_System.h"
#include "Export_Utility.h"


#include "HNPCIDLE.h"
#include "NonWeaponState.h"

#include "UI.h"

CHNPC::CHNPC(LPDIRECT3DDEVICE9 pGraphicDev)
	:CHuman(pGraphicDev)
{
}

CHNPC::CHNPC(const CHNPC& rhs)
	:CHuman(rhs)
{
}

CHNPC::~CHNPC()
{
}

HRESULT CHNPC::Ready_GameObject()
{
	m_eFlagpoleType = SQUARD_ID::SQUARD1;

	m_pState = CHNPCIDLE::Create(this);
	m_pWeaponState = CNonWeaponState::Create(this);

	return CHuman::Ready_GameObject();
}

_int CHNPC::Update_GameObject(const _float& fTimeDelta)
{
	return CHuman::Update_GameObject(fTimeDelta);
}

void CHNPC::LateUpdate_GameObject()
{
	CHuman::LateUpdate_GameObject();
}

void CHNPC::Render_GameObject()
{
	if (m_pUI != nullptr) {
		static_cast<CUI*>(m_pUI)->Set_HideCheck(false);
	}

	CHuman::Render_GameObject();
}

void CHNPC::OnCollisionEnter(CCollider* _pOther)
{
	//CCharacter* pCharacter = ;

	if (_pOther->Get_Owner()->Get_ObjectType() == OBJECTTYPE::MONSTER_BULLET) {

		if (m_bNonPushCheck == true) {
			Pushed(_pOther, 0.1f);
			
		}
		else {
			Pushed(_pOther, 0.3f);
			
		}
	}
}

void CHNPC::OnCollisionStay(CCollider* _pOther)
{
	CCharacter::OnCollisionStay(_pOther);

	//if (_pOther->Get_Owner()->Get_ObjectType() == m_eObjectType) {
	//	//Pushed(_pOther, 0.1f);
	//	Pushed_Character(_pOther, 0.1f);
	//}

	//if (_pOther->Get_Owner()->Get_ObjectType() == OBJECTTYPE::MONSTER) {
	//	//Pushed(_pOther, 1.f);
	//	Pushed_Character(_pOther, 0.1f);
	//}

	
}

void CHNPC::OnCollisionExit(CCollider* _pOther)
{
}

void CHNPC::Free()
{
	CHuman::Free();
}
