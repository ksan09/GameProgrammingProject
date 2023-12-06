#pragma once
#include "Scene.h"
class PlayerDieScene
	:public Scene
{
public:
	PlayerDieScene();
	~PlayerDieScene();
public:
	void Init() override;
	void Update() override;
	void Render(HDC _dc) override;
	void ReStart(HDC _dc, HWND hWnd);
private:
	int m_iFontSize;
};

