#pragma once
#include "Scene.h"
class EndingScene
	:public Scene
{
public:
	EndingScene();
	~EndingScene();
public:
	void Init() override;
	void Update() override;
	void Render(HDC _dc) override;
private:
	float m_iFontSize;
	int x;
	float y;
	float saveY;
	int idxNum;
    vector<wstring> strArr;
};

