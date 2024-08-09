#pragma once
#include "Engine_Typedef.h"
#include "Human.h"

class CHumanAnimation
{
public:
	explicit CHumanAnimation();
	virtual ~CHumanAnimation();

public:
	HRESULT Ready_PlayerState(CHuman* statePlayer, const _tchar* pStateTag);
	CHumanAnimation* Update_PlayerState(CHuman* statePlayer, const _tchar* pStateTag, const float& fTimeDelta);
public:
	void	Update_Animation(CHuman* statePlayer, const float& fTimeDelta);
	void	Update_Matrix(CHuman* statePlayer, const _int& iIndex, vector<FRAME*>& vecFrame);
public:
	vector<FRAME*> Find(const _tchar* pStateTag);
	void	Add_State(const _tchar* pStateTag);

private:
	FRAME* Create_Frame(vector<FRAME*>* vecPartsFrame);

private:
	map<const _tchar*, vector<FRAME*>> m_mapState;
	FRAME* m_pFrame=nullptr;

	_ulong				m_FrameCount;
	_float				m_fTotalFrameCount;
	_float				m_fStateFrame;
	_float				m_fSpeed;

private:
	//_vec3				m_vParts[PARTS_END][2];
public:
	static	CHumanAnimation* Create(CHuman* statePlayer, const _tchar* pStateTag);
public:
	void Free(CHuman* statePlayer);
	
};
