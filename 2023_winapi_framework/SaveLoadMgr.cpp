#include "pch.h"
#include "SaveLoadMgr.h"
#include <tchar.h>

void SaveLoadMgr::Init()
{
	hFile = CreateFile(L"SaveData.txt", 0, NULL,
		NULL, 3, NULL, NULL);
	WriteFile(hFile, _T("ABCDE"), 5, &dwWritten, NULL);
}

//void SaveLoadMgr::Save()
//{
//}
