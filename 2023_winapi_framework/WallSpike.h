#pragma once
#include "Object.h"
class Texture;
class WallSpike :
    public Object
{
public:
	WallSpike(float deleteTime, bool isLeft);
	~WallSpike();
public:
	void Update() override;

	void Render(HDC _dc) override;
private:
	Texture* m_pTex;
	float m_fDangerDelay;
	float m_fDeleteDelay;
	float m_fCurTime;
	bool m_isDie;
	bool m_isDangerEnd;
	bool m_isDanger;
	bool m_isLeft;
};

