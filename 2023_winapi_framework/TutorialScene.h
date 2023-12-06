#pragma once
#include "Scene.h"
#include "DefaultMonster.h"
class TutorialScene :
    public Scene
{
public:
	TutorialScene();
	~TutorialScene();
public:
	void Init() override;
	void Update() override;
	void Render(HDC _dc) override;
	virtual void Release() override;
public:
	DefaultMonster* m_monsterObj;
	float m_fCurTime;
};

