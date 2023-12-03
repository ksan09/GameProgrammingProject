#pragma once
#include "Node.h"
#include "Object.h"

class LastBossPatternNode1
	: public ActionNode
{
public:
	LastBossPatternNode1(Object* owner, Object* target);
	~LastBossPatternNode1();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	void ShotBullet();
private:
	Object* m_pOwner;
	Object* m_pTarget;
private:
	bool m_isAnim;
	bool m_isSkillOut;
	bool m_isSpikeSpawn;
	bool m_isDelay;
	bool m_isLeft;
	float m_fCurTime;
private:
	float m_fLeftPosX;
	float m_fRightPosX;
private:
	int m_iBulletCount;
	int m_iCurCount;
private:
	int m_iPattern;
	float m_fPatternY[3][16] = {
		{ 496.f, 464.f, 432.f, 464.f, 496.f, 368.f, 496.f, 464.f, 432.f, 464.f, 496.f, 368.f, 496.f, 432.f, 368.f, 304.f },
		{ 464.f, 464.f, 464.f, 368.f, 496.f, 432.f, 368.f, 496.f, 432.f, 496.f, 464.f, 432.f, 464.f, 496.f, 368.f, 496.f },
		{ 496.f, 432.f, 464.f, 496.f, 368.f, 496.f, 432.f, 464.f, 496.f, 368.f, 496.f, 432.f, 464.f, 496.f, 368.f, 496.f }
	};
};