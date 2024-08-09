#include "stdafx.h"
#include "..\Header\HMonster.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "HMIdle.h"
#include "NonWeaponState.h"
#include "ResourceMgr.h"


CHMonster::CHMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CHuman(pGraphicDev)
{
}

CHMonster::CHMonster(const CHMonster& rhs)
	:CHuman(rhs)
{
}

CHMonster::~CHMonster()
{
}

HRESULT CHMonster::Ready_GameObject()
{
	//m_eFlagpoleType = SQUARD_ID::SQUARD_ID_END;

	m_pState = CHMIdle::Create(this);
	m_pWeaponState = CNonWeaponState::Create(this);

	return CHuman::Ready_GameObject();
}

_int CHMonster::Update_GameObject(const _float& fTimeDelta)
{
	

	_vec3 vPos = *m_vTransform->Get_Pos();
	if (m_bDead) 
	{
		CResourceMgr::GetInstance()->Drop_Emerald(m_iCost, vPos);
		return S_OK;
	}

	return CHuman::Update_GameObject(fTimeDelta);
}

void CHMonster::LateUpdate_GameObject()
{
	CHuman::LateUpdate_GameObject();
}

void CHMonster::Render_GameObject()
{
	CHuman::Render_GameObject();
}

void CHMonster::OnCollisionEnter(CCollider* _pOther)
{
	//if (_pOther->Get_Owner()->Get_ObjectType() == OBJECTTYPE::ALLY_BULLET) {
	//	Pushed(_pOther,1.f);
	//}

	
}

void CHMonster::OnCollisionStay(CCollider* _pOther)
{
	CCharacter::OnCollisionStay(_pOther);
	//if (_pOther->Get_Owner()->Get_ObjectType() == OBJECTTYPE::MONSTER) {
	//	Pushed(_pOther, 0.1f);
	//}

	//if (_pOther->Get_Owner()->Get_ObjectType() == OBJECTTYPE::PLAYER) {
	//	//Pushed(_pOther, 1.f);
	//}

	
}

void CHMonster::OnCollisionExit(CCollider* _pOther)
{
}

void CHMonster::Free()
{
	CResourceMgr::GetInstance()->Add_Money(m_iCost);
	CHuman::Free();
}
