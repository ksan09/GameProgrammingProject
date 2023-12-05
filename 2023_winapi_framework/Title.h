#pragma once
#include "Object.h"
class Texture;
class Title :
	public Object
{
public:
	Title();
	~Title();
public:
	virtual void Update() override;
	void Render(HDC _dc) override;
private:
	Texture* m_pTex;
	int index;
public:
	int curIndex;
	bool onGameRule;
};

