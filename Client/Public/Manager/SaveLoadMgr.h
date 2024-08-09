#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CSaveLoadMgr :
    public CBase
{
    DECLARE_SINGLETON(CSaveLoadMgr)

private:
    explicit    CSaveLoadMgr();
    virtual     ~CSaveLoadMgr();
public:
    HRESULT     Ready_SaveLoadMgr();
public:
    HRESULT     Read_AnimationDataFile();
    HRESULT     Read_MonAnimationDataFile();
    HRESULT     Read_ItemPartsDataFile();
    HRESULT     Read_ItemTotalDataFile();
private:
    HRESULT      Load_AnimationData(const _tchar* cFilePath,vector<FRAME*>& vecFrame);
    HRESULT      Load_MonAnimationData(const _tchar* cFilePath, vector<MONSTERFRAME*>& vecFrame);
    HRESULT      Load_ItemPartsData(const _tchar* cFilePath, vector<PARTSITEMINFO*>& vecFrame);
    HRESULT      Load_ItemTotalData(const _tchar* cFilePath, TOTALITEMINFO* pTotalItem);
public:
    vector<FRAME*>* Get_AnimationData(const _tchar* tKey);
    vector<MONSTERFRAME*>* Get_MonAnimationData(const _tchar* tKey);
    vector<PARTSITEMINFO*>* Get_ItemPartsInfoData(const _tchar* tKey);
    TOTALITEMINFO* Get_ItmeTotalInfoData(const _tchar* tKey);
private:
    map<const _tchar*, vector<FRAME*>> m_mapAnimation;
    map<const _tchar*, vector<MONSTERFRAME*>> m_mapMonAnimation;
    map<const _tchar*, vector<PARTSITEMINFO*>> m_mapItemParts;
    map<const _tchar*, TOTALITEMINFO*> m_mapItemTotal;

    vector<const _tchar*> m_vecKKey;
private:
    virtual void    Free();
};

END

