#pragma once
#include "Block.h"
class WarningObject
	: public Object
{
public:
	WarningObject(float deleteTime);
	~WarningObject();
public:
	void Update() override;

	void Render(HDC _dc) override;
private:
	float m_fDangerDelay;
	float m_fDeleteDelay;
	float m_fCurTime;
	bool m_isDie;
	bool m_isDangerEnd;
	bool m_isDanger;
};

