#pragma once
#include "Object.h"
class Texture;
class GameRule
	: public Object
{
public:
	GameRule();
	~GameRule();
public:
	virtual void Update() override;
	void Render(HDC _dc);
public:
	bool RulePopUp;
private:
	Texture* m_pTex;
};

