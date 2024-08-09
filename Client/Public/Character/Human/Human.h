#pragma once
#include "Transform.h"
#include "ImGuiMgr.h"
#include "MeleeATTCol.h"
#include "Character.h"
#include "CharacterState.h"
#include "BlockMap.h"

class CHumanAnimation;
class CWeaponState;
class CCubeItem;
class CHumanState;

BEGIN(Engine)

class CRcTex;
class CRcTexBottom;
class CCubeTex;
class CCubeTexTop;

class CTexture;
//class CTransform;
class CCalculator;
class CRigidBody;

END

class CHuman : public CCharacter
{
protected:
	explicit CHuman(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHuman(const CHuman& rhs);
	virtual ~CHuman();
public:
	virtual HRESULT Ready_GameObject() ;
	virtual _int	Update_GameObject(const _float& fTimeDelta) ;
	virtual void	LateUpdate_GameObject() ;
	virtual void	Render_GameObject();
	


public: // �ִϸ��̼�
	void	Animation_Frame(const float& fTimeDelta);
	void	Update_Matrix(const _int& iIndex, vector<FRAME*>& vecFrame);
	void	Animation_Total_Frame_Setting(const _int& iIndex, vector<FRAME*>& vecFrame);
public:
	
	virtual HRESULT	Add_Component() PURE;
	
protected:
	HRESULT			SetUp_Parts(const _tchar* Head,
		const _tchar* Body,
		const _tchar* Arm1,
		const _tchar* Arm2,
		const _tchar* Leg1,
		const _tchar* Leg2);
	HRESULT			Default_Ratio();

public:
	void RotateParts(PARTS part, ROTATION eType, const _float& fAngle, const _float& fTimeDelta)
	{
		m_pTransformCom[part]->Rotation(eType, D3DXToRadian(fAngle * fTimeDelta));
	}
	CTransform** Get_Parts_Transform() { return m_pTransformCom; }

public:
	void					Set_Destination();
	void					Create_Bullet();

	bool					Is_Animation_Frame_End();

	void					Update_Dir_To_Destination() 
	{
		if (m_bIsRotate) return;

		_vec3 vDir;
		D3DXVec3Normalize(&vDir, &Calc_Distance_To_Destination());
		m_pTransformCom[TOTAL]->m_vAngle.y = atan2f(vDir.x, vDir.z);
	};

	vector<FRAME*>*			Get_VecFrame() { return m_pVecFrame; };
	void					Set_VecFrame(vector<FRAME*>* _pVecFrame) 
	{ 
		Init_FrameCount();
		Set_FrameSpeed(1.f);
		m_pVecFrame = _pVecFrame; 
	};
	_float					Get_FrameSpeed() { return m_fFrameSpeed; };
	void					Set_FrameSpeed(_float	_fFrameSpeed) { m_fFrameSpeed = _fFrameSpeed; };

	

public:
	_bool					Attack_Stance(const _float& fRange);	// ������ ������ ��� ���� ����


public:
	void					Init_Pos(const _vec3& vPos) {
		m_vTransform->Set_Pos(vPos);
		m_vPickPos = *m_vTransform->Get_Pos();
		m_pTransformCom[TOTAL]->Set_Pos(m_vTransform->m_vInfo[INFO_POS]);
	}			// ó�� ��ġ �� �� Ÿ�� ��ġ ����
public:
	void		Set_Dance() { m_bDance = true; }
	_bool		Get_Dance() { return m_bDance; }
protected:
	_vec3					Picking_On_Terrain();
		
protected: // ���� ���� ����
	CCubeTexTop* m_pBufferCom[PARTS_END];
	CTransform* m_pTransformCom[PARTS_END];
	CTexture* m_pTextureCom[PARTS_END];
	CCalculator* m_pCalculatorCom[PARTS_END];
protected:
	vector<FRAME*>* m_pVecFrame;
protected:
	_bool		m_bDance = false;
protected:
	virtual void Free();

//public:
//	virtual			HRESULT Add_Weapon(WEAPONTYPE eWeaponType);
//	void			Delete_Weapon();
//	HRESULT			Add_SubWeapon(WEAPONTYPE eWeaponType); // ����ü ����
//	void			Delete_SubWeapon(); 
//	CGameObject*	Get_SubWeapon() { return m_pSubWeapon; }

//public:
	/*bool					Is_Arrived();
	void					Move(const _float& fTimeDelta, const _float& fSpeed=5.f);



	void					Init_FrameCount(_ushort _sCount = 0) { m_FrameCount = _sCount; };*/

//public:
	/*WEAPONTYPE				Get_WeaponType(){ return m_eWeaponType; };
	void					Set_WeaponType(WEAPONTYPE _eWeaponType) {m_eWeaponType = _eWeaponType;};

	void					Set_IsRotate(bool _bIsRotate) { m_bIsRotate = _bIsRotate; };*/

//public:
	//void					Create_ATTColl(const _float& fDeadTime, const _vec3& vScale, const _float& fDist,OBJECTTYPE eObjType,CGameObject* pOwner);	// ���ݽ� ���� �ݸ��� ����

	//void					LookAt_Target();	// Ÿ������

	//void					Guide(const _float& fTimeDelta);								// Ÿ���� ����
	//void					Pushed(CCollider* _pOther, const _float& fSpeed);				// ������

	//void					Target_Dir_Update();

//public:
//	void					Ready_Dead();				// �״� ����
//	void					Cut_HP(_int iDamage) { m_iHP -= iDamage; }
//	_int&					Get_HP() { return m_iHP; }
//
//	void					Set_Damage(_int iDamage) { m_iDamage = iDamage; }
//	_int&					Get_Damage() { return m_iDamage; }

//public:
//	void					Set_PickPos(const _vec3& vTargetPos) { m_vPickPos = vTargetPos; } // ��ǥ ���� ����
//	_int					Get_Combat_Power() { return m_iCombat_Power; }
//
//	void					Set_InitLook() { m_vTransform->Get_Info(INFO_LOOK, &m_InitTotLook);
//	}
//
//	_vec3					Get_InitLook() { return m_InitTotLook; }
//
//public:
//	void					Set_Route(vector<POINT> vecRoute) 
//	{  
//		m_sRouteCount = 0;
//		m_vecRoute = vecRoute; 
//	}
//	vector<POINT>			Get_Route() { return m_vecRoute; }

//protected:
	//_vec3					Calc_Distance_To_Destination();
	//CRigidBody*		m_pRigidBody = nullptr;
//protected: // ���� ���� ����
//	
//	CHumanState*	m_pState ;
//	WEAPONTYPE		m_eWeaponType= WEAPONTYPE::WEAPON_END;
//	CWeaponState*	m_pWeaponState=nullptr;
//	CCubeItem*		m_pWeapon = nullptr;
//	CGameObject*	m_pSubWeapon = nullptr;
//
//protected: // �ִϸ��̼� ���� ����
//	_ulong			m_FrameCount;
//	_float			m_fTotalFrameCount;
//	_float			m_fFrameSpeed;
//	vector<FRAME*>* m_pVecFrame;
//
//	_vec3			m_InitTotPos;				// total �ִϸ��̼��� �������� ������ ���� ��ġ �ʱ� ���� ����
//	_vec3			m_InitTotRot;				// total �ִϸ��̼��� �������� ������ ���� ���� �ʱ� ���� ����
//	_vec3			m_InitTotLook;				// total Look ������ �����ϱ� ����
//
//protected: // �̵� �� ���� ���� ����
//	_vec3			m_vPickPos;
//	bool			m_bIsRotate;
//
//protected: // ����
//	_int			m_iHP = 0.f;			// ü��
//	_int			m_iDamage = 0.f;		// ���ݷ�
//	_int			m_iCombat_Power = 0.f;  // ������ -> �� �����¿� ���� ���� ���̺꿡 ������ �ٸ��� �����ϱ� ���ؼ�
//	_float			m_iAttackRange = 0.f;	// ���� ���� ����
//
//protected: // Astar ���� ����
//	vector<POINT>	m_vecRoute;				// ��ã�� �˰��������κ��� ���� ��ǥ ����
//	_ushort			m_sRouteCount = 0;
	

};

