#include "stdafx.h"
#include "..\Header\SaveLoadMgr.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "commdlg.h"
#include "shlwapi.h"
#include <wchar.h>

IMPLEMENT_SINGLETON(CSaveLoadMgr)

CSaveLoadMgr::CSaveLoadMgr()
{

}
CSaveLoadMgr::~CSaveLoadMgr()
{
	Free();
}

HRESULT CSaveLoadMgr::Ready_SaveLoadMgr()
{
	return S_OK;
}

HRESULT CSaveLoadMgr::Read_AnimationDataFile()
{
	WIN32_FIND_DATA	findFileData;

	string str = (string)ANIMATIONPATH;
	wstring ff(ANIMATIONPATH, &ANIMATIONPATH[str.length()]);
	wstring folder = ff + L"/*.dat";

	HANDLE hFind = FindFirstFileW(folder.c_str(), &findFileData);

	if (hFind != INVALID_HANDLE_VALUE) {

		do {

			wstring wstr = (wstring)(findFileData.cFileName);

			int iLen = wstr.find_last_of(L"_");
			int iLen2 = wstr.find_last_of(L".");
			int iLen3 = wstr.length();

			wstring wName = wstr.substr(0, iLen);
			wstring wKey = wstr.substr(iLen + 1, (iLen3 - iLen - 4 - 1));
			
			int iKeyLen = wKey.length() + 1;

			_tchar cFullPath[MAX_PATH] = L"../../Data/Animation/";
			const _tchar* cTemp = (const _tchar*)wstr.c_str();
			const _tchar* cWstr = (const _tchar*)wName.c_str();
			_tchar* cWKey = new _tchar[iKeyLen];
			lstrcpyW(cWKey, wKey.c_str());
			m_vecKKey.push_back(cWKey);
			
			lstrcat(cFullPath, (const _tchar*)wstr.c_str());
			//lstrcat(cFull, (const _tchar*)ANIMATIONPATH);

			vector<FRAME*> vecFrame;
			FAILED_CHECK_RETURN( Load_AnimationData(cFullPath, vecFrame),E_FAIL);

			/*if (strcmp("HUMAN", cWstr)) {
				int a = 0;
			}
			else if (strcmp("Quadrupedal", cWstr)) {

			}
			else if (strcmp("Item", cWstr)) {

			}
			else if (strcmp("Special", cWstr)) {

			}*/

			m_mapAnimation.insert({ cWKey,vecFrame });
			int a = 0;

		} while (FindNextFile(hFind,&findFileData) != 0);

		FindClose(hFind);
	}

	

	return S_OK;
}

HRESULT CSaveLoadMgr::Read_MonAnimationDataFile()
{
	WIN32_FIND_DATA	findFileData;

	string str = (string)MONANIMATIONPATH;
	wstring ff(MONANIMATIONPATH, &MONANIMATIONPATH[str.length()]);
	wstring folder = ff + L"/*.dat";

	HANDLE hFind = FindFirstFileW(folder.c_str(), &findFileData);

	if (hFind != INVALID_HANDLE_VALUE) {

		do {

			wstring wstr = (wstring)(findFileData.cFileName);

			int iLen = wstr.find_last_of(L"_");
			int iLen2 = wstr.find_last_of(L".");
			int iLen3 = wstr.length();

			wstring wName = wstr.substr(0, iLen);
			wstring wKey = wstr.substr(iLen + 1, (iLen3 - iLen - 4 - 1));

			int iKeyLen = wKey.length() + 1;

			_tchar cFullPath[MAX_PATH] = L"../../Data/MonAnimation/";
			const _tchar* cTemp = (const _tchar*)wstr.c_str();
			const _tchar* cWstr = (const _tchar*)wName.c_str();
			_tchar* cWKey = new _tchar[iKeyLen];
			lstrcpyW(cWKey, wKey.c_str());
			m_vecKKey.push_back(cWKey);

			lstrcat(cFullPath, (const _tchar*)wstr.c_str());
			//lstrcat(cFull, (const _tchar*)ANIMATIONPATH);

			vector<MONSTERFRAME*> vecFrame;
			FAILED_CHECK_RETURN(Load_MonAnimationData(cFullPath, vecFrame), E_FAIL);

		

			m_mapMonAnimation.insert({ cWKey,vecFrame });
			int a = 0;

		} while (FindNextFile(hFind, &findFileData) != 0);

		FindClose(hFind);
	}

	return S_OK;
}

HRESULT CSaveLoadMgr::Read_ItemPartsDataFile()
{
	WIN32_FIND_DATA	findFileData;

	string str = (string)ITEMPARTSINFOPATH;
	wstring ff(ITEMPARTSINFOPATH, &ITEMPARTSINFOPATH[str.length()]);
	wstring folder = ff + L"/*.dat";

	HANDLE hFind = FindFirstFileW(folder.c_str(), &findFileData);

	if (hFind != INVALID_HANDLE_VALUE) {

		do {

			wstring wstr = (wstring)(findFileData.cFileName);

			int iLen = wstr.find_last_of(L"_");
			int iLen2 = wstr.find_last_of(L".");
			int iLen3 = wstr.length();

			wstring wName = wstr.substr(0, iLen);
			wstring wKey = wstr.substr(iLen + 1, (iLen3 - iLen - 4 - 1));

			int iKeyLen = wKey.length() + 1;

			_tchar cFullPath[MAX_PATH] = L"../../Data/ObjectPartsInfo/";
			const _tchar* cTemp = (const _tchar*)wstr.c_str();
			const _tchar* cWstr = (const _tchar*)wName.c_str();
			_tchar* cWKey = new _tchar[iKeyLen];
			lstrcpyW(cWKey, wKey.c_str());
			m_vecKKey.push_back(cWKey);

			lstrcat(cFullPath, (const _tchar*)wstr.c_str());
			//lstrcat(cFull, (const _tchar*)ANIMATIONPATH);

			vector<PARTSITEMINFO*> vecItemParts;
			FAILED_CHECK_RETURN(Load_ItemPartsData(cFullPath, vecItemParts), E_FAIL);


			m_mapItemParts.insert({ cWKey,vecItemParts });
			int a = 0;

		} while (FindNextFile(hFind, &findFileData) != 0);
		FindClose(hFind);
	}


	return S_OK;
}

HRESULT CSaveLoadMgr::Read_ItemTotalDataFile()
{
	WIN32_FIND_DATA	findFileData;

	string str = (string)ITEMTOTALINFOPATH;
	wstring ff(ITEMTOTALINFOPATH, &ITEMTOTALINFOPATH[str.length()]);
	wstring folder = ff + L"/*.dat";

	HANDLE hFind = FindFirstFileW(folder.c_str(), &findFileData);

	if (hFind != INVALID_HANDLE_VALUE) {

		do {

			wstring wstr = (wstring)(findFileData.cFileName);

			int iLen = wstr.find_last_of(L"_");
			int iLen2 = wstr.find_last_of(L".");
			int iLen3 = wstr.length();

			wstring wName = wstr.substr(0, iLen);
			wstring wKey = wstr.substr(iLen + 1, (iLen3 - iLen - 4 - 1));

			int iKeyLen = wKey.length() + 1;

			_tchar cFullPath[MAX_PATH] = L"../../Data/ObjectTotalInfo/";
			const _tchar* cTemp = (const _tchar*)wstr.c_str();
			const _tchar* cWstr = (const _tchar*)wName.c_str();
			_tchar* cWKey = new _tchar[iKeyLen];
			lstrcpyW(cWKey, wKey.c_str());
			m_vecKKey.push_back(cWKey);

			lstrcat(cFullPath, (const _tchar*)wstr.c_str());
			//lstrcat(cFull, (const _tchar*)ANIMATIONPATH);

			TOTALITEMINFO* ItemTotal= new TOTALITEMINFO;
			FAILED_CHECK_RETURN(Load_ItemTotalData(cFullPath, ItemTotal), E_FAIL);


			m_mapItemTotal.insert({ cWKey,ItemTotal });
			

		} while (FindNextFile(hFind, &findFileData) != 0);
		FindClose(hFind);
	}


	return S_OK;
}

HRESULT CSaveLoadMgr::Load_AnimationData(const _tchar* cFilePath, vector<FRAME*>& vecFrame)
{
	HANDLE hFile = CreateFile(cFilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	//C: / Users / 조우택 / Desktop / SR_TeamMinever2 / Data / Animation / HUMAN_TEST.dat
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte = 0;
	DWORD	dwStrByte = 0;
	FRAME* pFrame = nullptr;

	ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

	CHAR* pTag = new CHAR[dwStrByte];

	ReadFile(hFile, pTag, dwStrByte, &dwByte, nullptr);

	Safe_Delete_Array(pTag);

	_float fSpeed(0.f);

	ReadFile(hFile, &fSpeed, sizeof(_float), &dwByte, nullptr);

	while (true)
	{
		pFrame = new FRAME[(_uint)PARTS::PARTS_END];

		ReadFile(hFile, pFrame, sizeof(FRAME[(_uint)PARTS::PARTS_END]), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pFrame);
			break;
		}

		vecFrame.push_back(pFrame);
		
	}

	CloseHandle(hFile);

	return S_OK;
}

HRESULT CSaveLoadMgr::Load_MonAnimationData(const _tchar* cFilePath, vector<MONSTERFRAME*>& vecFrame)
{
	HANDLE hFile = CreateFile(cFilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	//C: / Users / 조우택 / Desktop / SR_TeamMinever2 / Data / Animation / HUMAN_TEST.dat
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte = 0;
	DWORD	dwStrByte = 0;
	MONSTERFRAME* pFrame = nullptr;

	ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

	CHAR* pTag = new CHAR[dwStrByte];

	ReadFile(hFile, pTag, dwStrByte, &dwByte, nullptr);

	Safe_Delete_Array(pTag);

	_float fSpeed(0.f);

	ReadFile(hFile, &fSpeed, sizeof(_float), &dwByte, nullptr);

	while (true)
	{
		pFrame = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];

		ReadFile(hFile, pFrame, sizeof(MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END]), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pFrame);
			break;
		}

		vecFrame.push_back(pFrame);

	}

	CloseHandle(hFile);

	return S_OK;
}

HRESULT CSaveLoadMgr::Load_ItemPartsData(const _tchar* cFilePath, vector<PARTSITEMINFO*>& vecFrame)
{
	HANDLE hFile = CreateFile(cFilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte = 0;

	PARTSITEMINFO* pItemPartsInfo = nullptr;

	while (true)
	{
		pItemPartsInfo = new PARTSITEMINFO;

		ReadFile(hFile, pItemPartsInfo, sizeof(PARTSITEMINFO), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pItemPartsInfo);
			break;
		}

		vecFrame.push_back(pItemPartsInfo);
	}

	CloseHandle(hFile);

	return S_OK;
}

HRESULT CSaveLoadMgr::Load_ItemTotalData(const _tchar* cFilePath, TOTALITEMINFO* pTotalItem)
{
	HANDLE hFile = CreateFile(cFilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte = 0;
	DWORD	dwStrByte = 0;

	ReadFile(hFile, pTotalItem, sizeof(TOTALITEMINFO), &dwByte, nullptr);

	CloseHandle(hFile);

	return S_OK;
}

vector<FRAME*>* CSaveLoadMgr::Get_AnimationData(const _tchar* tKey)
{
	auto iter = find_if(m_mapAnimation.begin(), m_mapAnimation.end(), CTag_Finder(tKey));

	if (iter == m_mapAnimation.end())
		return nullptr;

	return &(iter->second);
}

vector<MONSTERFRAME*>* CSaveLoadMgr::Get_MonAnimationData(const _tchar* tKey)
{
	auto iter = find_if(m_mapMonAnimation.begin(), m_mapMonAnimation.end(), CTag_Finder(tKey));

	if (iter == m_mapMonAnimation.end())
		return nullptr;

	return &(iter->second);
}

vector<PARTSITEMINFO*>* CSaveLoadMgr::Get_ItemPartsInfoData(const _tchar* tKey)
{
	auto iter = find_if(m_mapItemParts.begin(), m_mapItemParts.end(), CTag_Finder(tKey));

	if (iter == m_mapItemParts.end())
		return nullptr;

	return &(iter->second);
}

TOTALITEMINFO* CSaveLoadMgr::Get_ItmeTotalInfoData(const _tchar* tKey)
{
	auto iter = find_if(m_mapItemTotal.begin(), m_mapItemTotal.end(), CTag_Finder(tKey));

	if (iter == m_mapItemTotal.end())
		return nullptr;

	return (*iter).second;
}

void CSaveLoadMgr::Free()
{
	
	for (auto& iter : m_mapAnimation) {
		for (auto& iter2 : iter.second) {
			Safe_Delete(iter2);
		}
		iter.second.clear();
	}
	m_mapAnimation.clear();

	for (auto& iter : m_mapMonAnimation) {
		for (auto& iter2 : iter.second) {
			Safe_Delete(iter2);
		}
		iter.second.clear();
	}
	m_mapMonAnimation.clear();

	for (auto& iter : m_mapItemParts) {
		for (auto& iter2 : iter.second) {
			Safe_Delete(iter2);
		}
		iter.second.clear();
	}
	m_mapItemParts.clear();
	
	for (auto& iter : m_mapItemTotal) {
		Safe_Delete(iter.second);
	}
	m_mapItemTotal.clear();
	
	for_each(m_vecKKey.begin(), m_vecKKey.end(), CDeleteArrayObj());
	m_vecKKey.clear();
	
}
