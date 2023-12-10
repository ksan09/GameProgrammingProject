#pragma once
class SaveLoadMgr
{
	SINGLE(SaveLoadMgr);
private:
    HANDLE hFile;
    TCHAR saveData[1];
    WORD wd;
    DWORD dwWritten;
public:
    void Init();
    void Save();
};

