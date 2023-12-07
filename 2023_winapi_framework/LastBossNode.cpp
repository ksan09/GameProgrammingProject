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
#include "Animator.h"
#include "Core.h"
#include "AutoBullet.h"
#include "Danger.h"

LastBossPatternNode1::LastBossPatternNode1(Object* owner, Object* target)
	: m_pOwner(owner)
	, m_pTarget(target)
	, m_isAnim(false)
	, m_isSpikeSpawn(0)
	, m_isLeft(false)
	, m_fCurTime(0.f)
	, m_fLeftPosX(32.f)
	, m_fRightPosX(WINDOW_WIDTH - 32)
	, m_isDelay(false)
	, m_iCurCount(0)
	, m_iBulletCount(15)
	, m_iPattern(0)
	, m_isSkillOut(false)
{

}

LastBossPatternNode1::~LastBossPatternNode1()
{
}

void LastBossPatternNode1::OnStart()
{
	m_pOwner->SetPos(Vec2(WINDOW_WIDTH / 2.f + 4, 96.f + 6.f));

	m_pOwner->GetAnimator()->PlayAnim(L"LB_Skill", false);
	m_pOwner->GetAnimator()->Reset();

	m_isLeft = rand() % 2;
	m_fCurTime = 0.f;
	m_isSpikeSpawn = false;
	m_isDelay = false;
	m_iCurCount = 0;
	m_iPattern = rand() % 3;
	m_isAnim = false;

	
}

NODE_STATE LastBossPatternNode1::OnUpdate()
{
	m_fCurTime += fDT;
	if (m_isAnim == false)
	{
		if (m_fCurTime >= 0.3f)
		{
			ResMgr::GetInst()->Play(L"SpikeUp");
			Core::GetInst()->Shake(0.15f, 1.5f);

			m_fCurTime = 0.f;
			Vec2 pos = m_pTarget->GetPos();
			m_pTarget->SetPos(Vec2((m_isLeft ? m_fLeftPosX : m_fRightPosX), pos.y));
			m_isAnim = true;
		}
	}
	else if (m_isDelay == false)
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

		if (m_fCurTime >= 0.6f)
		{
			m_isDelay = true;
			m_pOwner->GetAnimator()->PlayAnim(L"LB_Idle", true);
			m_fCurTime = 0.f;
		}
	}
	else if (m_fCurTime < 2.5f)
	{
		// 방향으로 밀기
		Vec2 pos = m_pTarget->GetPos();
		pos.x += (m_isLeft ? -200 : 200) * fDT;
		if (pos.x < 0)
			pos.x = 0;
		else if (pos.x > WINDOW_WIDTH)
			pos.x = WINDOW_WIDTH;
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
	bullet->SetPos(Vec2((float)(m_isLeft ? WINDOW_WIDTH : 0), m_fPatternY[m_iPattern][m_iCurCount - 1]));
	bullet->GetRigidbody2D()->SetVelocity(Vec2((m_isLeft ? -1.f : 1.f) * 500.f, 0.f));
	SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
}

LastBossPatternNode2::LastBossPatternNode2(Object* owner, Object* target)
	: m_pOwner(owner)
	, m_pTarget(target)
	, m_fCurTime(0)
	, m_isAnim(false)
	, m_isSkillOut(false)
	, m_isDelay(false)
	, m_iBulletCount(10)
	, m_iCurCount(0)
	, m_iDirX(1)
	, m_isAppear(false)
{
}

LastBossPatternNode2::~LastBossPatternNode2()
{
}

void LastBossPatternNode2::OnStart()
{
	ShotBullet();

	m_fCurTime = 0;
	m_iCurCount = 0;
	m_isAnim = false;
	m_isSkillOut = false;
	m_isDelay = false;
	m_isAppear = false;

	Danger* danger = new Danger();
	SceneMgr::GetInst()->GetCurScene()->AddObject(danger, OBJECT_GROUP::EFFECT);
}

NODE_STATE LastBossPatternNode2::OnUpdate()
{
	m_fCurTime += fDT;
	if (m_isAppear == false)
	{
		if (m_fCurTime >= 1.f)
		{
			m_fCurTime = 0.f;

			m_iDirX = (m_pOwner->GetPos().x - m_pTarget->GetPos().x);

			if (m_iDirX > 0) m_iDirX = -1;
			else m_iDirX = 1;

			m_pOwner->SetPos(Vec2(WINDOW_WIDTH / 2.f + 4, WINDOW_HEIGHT - 160.f - 28.f));

			m_pOwner->GetAnimator()->PlayAnim(L"LB_Skill", false);
			m_pOwner->GetAnimator()->Reset();

			m_isAppear = true;
		}
	}
	else if (m_isAnim == false)
	{
		if (m_fCurTime >= 0.3f)
		{
			ShotAutoBullet();
			ResMgr::GetInst()->Play(L"SpikeUp");
			Core::GetInst()->Shake(0.15f, 1.5f);

			m_fCurTime = 0.f;
			m_isAnim = true;
		}
	}
	else if (m_isDelay == false)
	{
		if (m_fCurTime >= 0.8f)
		{


			m_isDelay = true;
			m_pOwner->GetAnimator()->PlayAnim(L"LB_Move", true);
			m_fCurTime = 0.f;
		}
	}
	else
	{
		Vec2 pos = m_pOwner->GetPos();
		pos.x += m_iDirX * (m_iCurCount % 3 == 1 ? 500.f : 200.f) * fDT;
		m_pOwner->SetPos(pos);

		if (m_fCurTime >= 0.4f)
		{
			ResMgr::GetInst()->Play(L"Bullet");
			m_fCurTime = 0.f;
			m_iCurCount++;

			m_iDirX = (m_pOwner->GetPos().x - m_pTarget->GetPos().x);

			if (m_iDirX > 0) m_iDirX = -1;
			else m_iDirX = 1;

			Bullet* bullet = new Bullet();
			bullet->SetPos(m_pOwner->GetPos());
			bullet->GetRigidbody2D()->SetVelocity({ 0, -800 });
			SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
		}

		if (m_iCurCount >= m_iBulletCount)
		{
			return NODE_STATE::SUCCESS;
		}
	}

	return NODE_STATE::RUNNING;
}

void LastBossPatternNode2::OnStop()
{
}

void LastBossPatternNode2::ShotAutoBullet()
{
	ResMgr::GetInst()->Play(L"Bullet");
	for (int i = 0; i <= 6; ++i)
	{
		if (i == 0)
			continue;
		Vec2 dir = Vec2((3 - i), (-3));
		dir.Normalize();

		AutoBullet* bullet = new AutoBullet(m_pTarget);
		bullet->SetPos(m_pOwner->GetPos());
		bullet->GetRigidbody2D()->SetVelocity(Vec2(dir.x * 250, dir.y * 250));
		SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
	}
	

}

void LastBossPatternNode2::ShotBullet()
{
	ResMgr::GetInst()->Play(L"Bullet");
	for (int i = -1; i <= 1; ++i)
	{
		if (i == 0)
		{
			AutoBullet* bullet = new AutoBullet(m_pTarget);
			bullet->SetPos(m_pOwner->GetPos());
			bullet->GetRigidbody2D()->SetVelocity(Vec2(0, 250));
			SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
			continue;
		}

		Vec2 dir = Vec2((i), (3));
		dir.Normalize();
		
		AutoBullet* bullet = new AutoBullet(m_pTarget);
		bullet->SetPos(m_pOwner->GetPos());
		bullet->GetRigidbody2D()->SetVelocity(Vec2(dir.x * 250, dir.y * 250));
		SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
	}
}

LastBossPatternNode3::LastBossPatternNode3(Object* owner, Object* target)
	: m_pOwner(owner)
	, m_pTarget(target)
	, m_isAnim(false)
	, m_isSpikeSpawn(0)
	, m_isLeft(false)
	, m_fCurTime(0.f)
	, m_fLeftPosX(32.f)
	, m_fRightPosX(WINDOW_WIDTH - 32)
	, m_isDelay(false)
	, m_iCurCount(0)
	, m_iBulletCount(30)
	, m_iPattern(0)
	, m_isSkillOut(false)
	, m_isBullet(false)
{

}

LastBossPatternNode3::~LastBossPatternNode3()
{
}

void LastBossPatternNode3::OnStart()
{
	m_pOwner->SetPos(Vec2(WINDOW_WIDTH / 2.f + 4, 96.f + 6.f));

	m_pOwner->GetAnimator()->PlayAnim(L"LB_Skill", false);
	m_pOwner->GetAnimator()->Reset();

	m_isBullet = rand() % 2;
	m_isLeft = rand() % 2;
	m_fCurTime = 0.f;
	m_isSpikeSpawn = false;
	m_isDelay = false;
	m_iCurCount = 0;
	m_iPattern = rand() % 3;
	m_isAnim = false;


}

NODE_STATE LastBossPatternNode3::OnUpdate()
{
	m_fCurTime += fDT;
	if (m_isAnim == false)
	{
		if (m_fCurTime >= 0.3f)
		{
			ResMgr::GetInst()->Play(L"SpikeUp");
			Core::GetInst()->Shake(0.15f, 1.5f);

			m_fCurTime = 0.f;
			m_isAnim = true;

			WallSpike* sp = new WallSpike(4.5f, true);
			sp->SetPos({ 50, WINDOW_HEIGHT / 2 - 107 });
			SceneMgr::GetInst()->GetCurScene()->AddObject(sp, OBJECT_GROUP::OBJ);
			WallSpike* sp2 = new WallSpike(4.5f, false);
			sp2->SetPos({ WINDOW_WIDTH - 50, WINDOW_HEIGHT / 2 - 107 });
			SceneMgr::GetInst()->GetCurScene()->AddObject(sp2, OBJECT_GROUP::OBJ);
		}
	}
	else if (m_isDelay == false)
	{
		if (m_fCurTime >= 0.7f)
		{
			m_isDelay = true;
			m_pOwner->GetAnimator()->PlayAnim(L"LB_Idle", true);
			m_fCurTime = 0.f;
		}
	}
	else if (m_fCurTime < 3.f)
	{
		// 총알 및 몬스터 패턴
		if (m_iCurCount < m_iBulletCount && m_fCurTime >= 0.1f)
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

void LastBossPatternNode3::OnStop()
{
}

void LastBossPatternNode3::ShotBullet()
{
	if (m_pTarget == nullptr)
		return;

	ResMgr::GetInst()->Play(L"MobShot");

	int cnt = (m_iCurCount + 1) / 2;

	if (m_isBullet)
	{
		Bullet* bullet = new Bullet;
		bullet->SetPos(Vec2(m_fPatternX[m_iPattern][cnt - 1], m_fPatternY[m_iPattern][cnt - 1]));
		bullet->GetRigidbody2D()->SetVelocity(Vec2((m_fPatternX[m_iPattern][cnt - 1] > 500.f ? -1.f : 1.f) * 500.f, 0.f));
		SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
	}
	else
	{
		DefaultMonster* bullet = new DefaultMonster;
		//bullet->SetPos(Vec2(m_fPatternX[2][m_iCurCount - 1], m_fPatternY[2][m_iCurCount - 1]));
		bullet->SetPos(Vec2(m_fPatternX[m_iPattern][cnt - 1], m_fPatternY[m_iPattern][cnt - 1]));
		bullet->GetRigidbody2D()->SetUseGravity(false);
		bullet->SetBlock((Vec2(32.f, 32.f)));
		bullet->GetRigidbody2D()->SetVelocity(Vec2((m_fPatternX[m_iPattern][cnt - 1] > 500.f ? -1.f : 1.f) * 500.f, 0.f));
		SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
	}

	
}