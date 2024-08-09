#pragma once
#include "Engine_Typedef.h"
#include "Monster.h"

class CMonsterAnimation
{
public:
	explicit CMonsterAnimation();
	virtual ~CMonsterAnimation();

public:
	HRESULT Ready_PlayerState(CMonster* statePlayer, const _tchar* pStateTag);
	CMonsterAnimation* Update_PlayerState(CMonster* statePlayer, const _tchar* pStateTag, const float& fTimeDelta);
public:
	void	Update_Animation(CMonster* statePlayer, const float& fTimeDelta);
	void	Update_Matrix(CMonster* statePlayer, const _int& iIndex, vector<MONSTERFRAME*>& vecFrame);
public:
	vector<MONSTERFRAME*> Find(const _tchar* pStateTag);
	void	Add_State(const _tchar* pStateTag);

private:
	MONSTERFRAME* Create_Frame(vector<MONSTERFRAME*>* vecPartsFrame);

private:
	map<const _tchar*, vector<MONSTERFRAME*>> m_mapState;
	MONSTERFRAME* m_pFrame = nullptr;

	_ulong				m_FrameCount;
	_float				m_fTotalFrameCount;
	_float				m_fStateFrame;
	_float				m_fSpeed;

private:
	//_vec3				m_vParts[PARTS_END][2];
public:
	static	CMonsterAnimation* Create(CMonster* statePlayer, const _tchar* pStateTag);
public:
	void Free(CMonster* statePlayer);

};

