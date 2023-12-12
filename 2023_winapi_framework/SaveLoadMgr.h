#pragma once
class SaveLoadMgr
{
	SINGLE(SaveLoadMgr);
private:
    const char* s1c = "A";
    const char* s2c = "B";
    const char* s3c = "C";
    std::string saveStr;
public:
    void Init();
    void Stage1();
    void Stage2();
    void Stage3();
public:
    bool CS1();
    bool CS2();
    bool CS3();
    bool BossStage();
};

