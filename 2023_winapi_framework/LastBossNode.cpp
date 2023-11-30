#include "pch.h"
#include "LastBossNode.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "DefaultMonster.h"
#include "Spike.h"
#include "Bullet.h"
#include "ResMgr.h"
#include "WallSpike.h"

LastBossPatternNode1::LastBossPatternNode1(Object* target)
	: m_pTarget(target)
	, m_isSpikeSpawn(0)
	, m_isLeft(false)
	, m_fCurTime(0.f)
	, m_fLeftPosX(32.f)
	, m_fRightPosX(WINDOW_WIDTH - 32)
	, m_isDelay(false)
	, m_iCurCount(0)
	, m_iBulletCount(15) 
{

}

LastBossPatternNode1::~LastBossPatternNode1()
{
}

void LastBossPatternNode1::OnStart()
{
	m_isLeft = rand() % 2;
	m_fCurTime = 0.f;
	m_isSpikeSpawn = false;
	m_isDelay = false;
	m_iCurCount = 0;

	Vec2 pos = m_pTarget->GetPos();
	m_pTarget->SetPos(Vec2((m_isLeft ? m_fLeftPosX : m_fRightPosX), pos.y));
}

NODE_STATE LastBossPatternNode1::OnUpdate()
{
	m_fCurTime += fDT;
	if (m_isDelay == false)
	{
		// 가시 소환
		if (m_isSpikeSpawn == false)
		{
			WallSpike* sp = new WallSpike(4.5f, m_isLeft);
			if (m_isLeft)
				sp->SetPos({ 50, WINDOW_HEIGHT / 2 - 107 });
			else
				sp->SetPos({ WINDOW_WIDTH - 50, WINDOW_HEIGHT / 2 - 107 });
			SceneMgr::GetInst()->GetCurScene()->AddObject(sp, OBJECT_GROUP::OBJ);
		}
		m_isSpikeSpawn = true;

		if (m_fCurTime >= 1.f)
		{
			m_isDelay = true;
			m_fCurTime = 0.f;
		}
	}
	else if (m_fCurTime < 2.f)
	{
		// 방향으로 밀기
		Vec2 pos = m_pTarget->GetPos();
		pos.x += (m_isLeft ? -200 : 200) * fDT;
		m_pTarget->SetPos(pos);

		// 총알 및 몬스터 패턴
		if (m_iCurCount < m_iBulletCount && m_fCurTime >= 0.2f)
		{
			m_fCurTime = 0;
			m_iCurCount++;
			ShotBullet();
		}
	}
	else
	{
		return NODE_STATE::SUCCESS;
	}


	return NODE_STATE::RUNNING;
}

void LastBossPatternNode1::OnStop()
{
}

void LastBossPatternNode1::ShotBullet()
{
	if (m_pTarget == nullptr)
		return;

	ResMgr::GetInst()->Play(L"Bullet");

	Vec2 targetPos = m_pTarget->GetPos();

	Bullet* bullet = new Bullet;
	bullet->SetPos(Vec2((float)(m_isLeft ? WINDOW_WIDTH : 0), m_fPatternY[0][m_iCurCount - 1]));
	bullet->GetRigidbody2D()->SetVelocity(Vec2((m_isLeft ? -1.f : 1.f) * 500.f, 0.f));
	SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
}
