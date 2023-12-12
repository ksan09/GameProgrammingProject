#include "pch.h"
#include "SaveLoadMgr.h"
#include <fstream>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

void SaveLoadMgr::Init()
{
	if (PathFileExistsA("stage1"))
		remove("stage1");
	if (PathFileExistsA("stage2"))
		remove("stage2");
	if (PathFileExistsA("stage3"))
		remove("stage3");
}

void SaveLoadMgr::Stage1()
{
	std::ofstream s1("stage1");
}

void SaveLoadMgr::Stage2()
{
	std::ofstream s2("stage2");
}

void SaveLoadMgr::Stage3()
{
	std::ofstream s3("stage3");
}

bool SaveLoadMgr::CS1()
{
	if (PathFileExistsA("stage1"))
		return true;
	return false;
}

bool SaveLoadMgr::CS2()
{
	if (PathFileExistsA("stage2"))
		return true;
	return false;
}

bool SaveLoadMgr::CS3()
{
	if (PathFileExistsA("stage3"))
		return true;
	return false;
}

bool SaveLoadMgr::BossStage()
{
	if (PathFileExistsA("stage1") 
		&& PathFileExistsA("stage2")
		&& PathFileExistsA("stage3"))
		return true;
	return false;
}

