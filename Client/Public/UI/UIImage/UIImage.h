#pragma once
#include "UI.h"
#include "SoundMgr.h"

class CUIImage :
    public CUI
{
protected:
	explicit CUIImage(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CUIImage(const CUIImage& rhs);
	virtual ~CUIImage();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject();

public:
	void	Set_CollCheck() 
	{ 
		CSoundManager::GetInstance()->StopSound(CHANNELID::SOUND_UI);
		CSoundManager::GetInstance()->PlaySound(L"select_pattern1.ogg", CHANNELID::SOUND_UI, 1.f);
		m_bCollCheck = true; 
	}
public:
	void		Set_Owner(CGameObject* pOwner) { m_pOwner = pOwner; }
protected:
	virtual HRESULT		Add_Component() PURE;
protected:
	void    Add_Count(const float& fTimeDelta) { m_fCount += fTimeDelta; };
	_float  Get_Count() { return m_fCount; };
protected:
	_bool		m_bCollCheck = false;
	_float     m_fCount = 0.f;
	CGameObject* m_pOwner = nullptr;
protected:
	virtual void Free() override;
};

