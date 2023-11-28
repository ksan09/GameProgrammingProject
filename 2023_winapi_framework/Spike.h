#pragma once
#include "Block.h"
class Spike
	: public Object
{
public:
	Spike(float deleteTime);
	~Spike();
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
};

