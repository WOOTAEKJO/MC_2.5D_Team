#pragma once
#include "GameObject.h"
#include "DamageableObject.h"

BEGIN(Engine)

class CCubeTexItem;
class CTexture;

END

class CCubeItem :
	public CDamageableObject
{
protected:
	explicit CCubeItem(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCubeItem(const CCubeItem& rhs);
	virtual ~CCubeItem();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();
public:
	HRESULT	Set_Item(const _tchar* tItemTag);	
	void	Render_Reset() {
		if (m_iCount == 0) {
			m_iCount++;
		}
		else if (m_iCount == 1 && !m_bRender) {
			m_bRender = true;
			m_iCount++;
		}
	}
public:
	void	Set_Owner(CGameObject* pObj) { m_Owner = pObj; }
protected:
	virtual HRESULT	Add_Component() { return S_OK; }
	virtual HRESULT	Default_Component(vector<PARTSITEMINFO*>& vecItemParts);

protected:
	WEAPONTYPE	m_eWeaponType;
protected:
	vector<CTransform*> m_vecTransCom;
	vector<CCubeTexItem*> m_vecBufferCom;
	vector<CTexture*> m_vecTextureCom;

	CGameObject* m_Owner = nullptr;
	PARTS		 m_OwnerParts = PARTS_END;

protected:
	vector<PARTSITEMINFO*>       m_vecItemParts;
	TOTALITEMINFO* m_pItemTotal = nullptr;		// 아이템의 전체적인 위치, 각도, 스케일 값
	vector<const _tchar*> m_vecKey;
protected: // 부모를 초기화 시 다시 세팅하기 위한 변수
	_vec3			m_vLook;		// 오너의 룩
	_vec3			m_vPos;			// 오너의 위치
	_vec3			m_vAngle;		// 오너의 각도

protected:
	_bool			m_bRender = false;
	_int			m_iCount = 0;
protected:
	virtual void Free();
};

