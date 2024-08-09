#pragma once

#include "Base.h"
#include "Character.h"
#include "Transform.h"
#include "ImGuiMgr.h"
#include "MeleeATTCol.h"

class CMonsterAnimation;
class CWeaponState;
class CCubeItem;
class CHumanState;

BEGIN(Engine)

class CRcTex;
class CRcTexBottom;
class CCubeTex;
class CBlockTex;
class CCubeTexTop;

class CTexture;
//class CTransform;
class CCalculator;
class CRigidBody;

END

class CMonster : public CCharacter
{
protected:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMonster(const CMonster& rhs);
	virtual ~CMonster();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();

public: // �ִϸ��̼�
	void	Animation_Frame(const float& fTimeDelta);
	void	Update_Matrix(const _int& iIndex, vector<MONSTERFRAME*>& vecFrame);
	void	Animation_Total_Frame_Setting(const _int& iIndex, vector<MONSTERFRAME*>& vecFrame);
public:

	virtual HRESULT	Add_Component() PURE;

protected:
	HRESULT			SetUp_Parts(const _tchar* Head,
		const _tchar* Body,
		const _tchar* Arm1,
		const _tchar* Arm2,
		const _tchar* Leg1,
		const _tchar* Leg2,
		const _tchar* ETC1,
		const _tchar* ETC2,
		const _tchar* ETC3,
		const _tchar* ETC4,
		const _tchar* ETC5,
		const _tchar* ETC6);
	HRESULT			Default_Ratio();

	void			ETC_Control(const _int& iIndex, vector<MONSTERFRAME*>& vecFrame);

public:
	void RotateParts(MONSTERPARTS part, ROTATION eType, const _float& fAngle, const _float& fTimeDelta)
	{
		m_pTransformCom[(_uint)part]->Rotation(eType, D3DXToRadian(fAngle * fTimeDelta));
	}
	CTransform** Get_Parts_Transform() { return m_pTransformCom; }

public:
	//void					Set_Destination();
	
	bool					Is_Animation_Frame_End();

	_bool					Attack_Stance(const _float& fRange);	// ������ ������ ��� ���� ����
	void					Update_Dir_To_Destination()
	{
		if (m_bIsRotate) return;

		_vec3 vDir;
		D3DXVec3Normalize(&vDir, &Calc_Distance_To_Destination());
		m_pTransformCom[TOTAL]->m_vAngle.y = atan2f(vDir.x, vDir.z);
	};

	vector<MONSTERFRAME*>* Get_VecFrame() { return m_pVecFrame; };
	void					Set_VecFrame(vector<MONSTERFRAME*>* _pVecFrame)
	{
		//NULL_CHECK(_pVecFrame);
		if (_pVecFrame == nullptr)
			return;
		Init_FrameCount();
		 Set_FrameSpeed(1.f);
		m_pVecFrame = _pVecFrame;
	};
	_float					Get_FrameSpeed() { return m_fFrameSpeed; };
	void					Set_FrameSpeed(_float	_fFrameSpeed) { m_fFrameSpeed = _fFrameSpeed; };

public:
	void					Init_Pos(const _vec3& vPos) {
		m_vTransform->Set_Pos(vPos);
		m_vPickPos = *m_vTransform->Get_Pos();
		m_pTransformCom[(_uint)MONSTERPARTS::TOTAL]->Set_Pos(m_vTransform->m_vInfo[INFO_POS]);
	}			// ó�� ��ġ �� �� Ÿ�� ��ġ ����
public:
	void		Set_ETCControl(_bool bChekc) { m_bETCControl = bChekc; }
	// etc �ִϸ��̼��� �ƴ� ���� ��Ʈ�� �Ǵ�
	_bool		Get_ETCControl() { return m_bETCControl; }
protected: // ���� ���� ����
	//CCubeTexTop* m_pBufferCom[(_uint)MONSTERPARTS::MONSTERPARTS_END];
	CCubeTexTop* m_pBufferCom[(_uint)MONSTERPARTS::ETC1];			// �⺻ ������
	CBlockTex* m_pETCBufferCom[(_uint)MONSTERETCPARTS::MONSTERETCPARTS_END];	// etc ������
	CTransform* m_pTransformCom[(_uint)MONSTERPARTS::MONSTERPARTS_END];
	CTexture* m_pTextureCom[(_uint)MONSTERPARTS::MONSTERPARTS_END];
	CCalculator* m_pCalculatorCom[(_uint)MONSTERPARTS::MONSTERPARTS_END];
protected:
	vector<MONSTERFRAME*>* m_pVecFrame;
	//vector<MONSTERPARTS*>   m_vecETC;
protected: //ETC ����
	_bool		m_bETCControl = false;	// etc �ִϸ��̼��� �ƴ� ���� ��Ʈ�� �Ǵ�
	_vec3		m_vETCSavePos;			// etc ��ġ�� ������ ���� ����
protected:
	_int		m_iTex_Num = 0;
protected:
	virtual void Free();

//public:
// 	   //void					Create_Bullet();
	//void					Init_FrameCount(_ushort _sCount = 0) { m_FrameCount = _sCount; };
// 	   //WEAPONTYPE				Get_WeaponType() { return m_eWeaponType; };
	//void					Set_WeaponType(WEAPONTYPE _eWeaponType) { m_eWeaponType = _eWeaponType; };

	//void					Set_IsRotate(bool _bIsRotate) { m_bIsRotate = _bIsRotate; };
	//bool					Is_Arrived();
	//void					Move(const _float& fTimeDelta, const _float& fSpeed = 5.f);
	//void					Create_ATTColl(const _float& fDeadTime, const _vec3& vScale, const _float& fDist, OBJECTTYPE eObjType, CGameObject* pOwner);	// ���ݽ� ���� �ݸ��� ����

	//void					LookAt_Target();	// Ÿ������

	//void					Guide(const _float& fTimeDelta);								// Ÿ���� ����
	//void					Pushed(CCollider* _pOther, const _float& fSpeed);				// ������

	//void					Target_Dir_Update();

//public:
	//void					Ready_Dead();				// �״� ����
	//void					Cut_HP(_int iDamage) { m_iHP -= iDamage; }
	//_int& Get_HP() { return m_iHP; }

	//void					Set_Damage(_int iDamage) { m_iDamage = iDamage; }
	//_int& Get_Damage() { return m_iDamage; }
//public:
//	virtual			HRESULT Add_Weapon(WEAPONTYPE eWeaponType);
//	void			Delete_Weapon();
//	HRESULT			Add_SubWeapon(WEAPONTYPE eWeaponType); // ����ü ����
//	void			Delete_SubWeapon();
//	CGameObject*	Get_SubWeapon() { return m_pSubWeapon; }

//public:
	//void					Set_PickPos(const _vec3& vTargetPos) { m_vPickPos = vTargetPos; } // ��ǥ ���� ����
	//_int					Get_Combat_Power() { return m_iCombat_Power; }

	/*void					Set_InitLook() {
		m_vTransform->Get_Info(INFO_LOOK, &m_InitTotLook);
	}*/

	//_vec3					Get_InitLook() { return m_InitTotLook; }

//public:
//	void					Set_Route(vector<POINT> vecRoute)
//	{
//		m_sRouteCount = 0;
//		m_vecRoute = vecRoute;
//	}
//	vector<POINT>			Get_Route() { return m_vecRoute; }

//protected:
	//_vec3					Picking_On_Terrain();
	//_vec3					Calc_Distance_To_Destination();


//protected:
	//CRigidBody* m_pRigidBody = nullptr;
//protected: // ���� ���� ����
//
//	CHumanState*	m_pState;
//	WEAPONTYPE		m_eWeaponType = WEAPONTYPE::WEAPON_END;
//	CWeaponState*	m_pWeaponState = nullptr;
//	CCubeItem*		m_pWeapon = nullptr;
//	CGameObject*	m_pSubWeapon = nullptr;
//
//protected: // �ִϸ��̼� ���� ����
//	_ulong				m_FrameCount;
//	_float				m_fTotalFrameCount;
//	_float				m_fFrameSpeed;
//	
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
//	vector<POINT>	m_vecRoute;				// ��ã�� �˰������κ��� ���� ��ǥ ����
//	_ushort			m_sRouteCount = 0;




};

