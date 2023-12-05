#include "pch.h"
#include "Boss2Node.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"
#include "EventMgr.h"
#include "Scene.h"
#include "Block.h"
#include "DefaultMonster.h"
#include "Spike.h"
#include "Bullet.h" 
#include "Object.h"

RandomPatternNode2::RandomPatternNode2()
	: m_iSelect(0)
{
}

RandomPatternNode2::~RandomPatternNode2()
{
}

void RandomPatternNode2::OnStart()
{
	if (m_pChildren.size() == 1)
		m_iSelect = 0;
	else
	{
		int idx = rand() % m_pChildren.size();
		if (idx == m_iSelect)
			m_iSelect = (idx + 1) % m_pChildren.size();
		else
			m_iSelect = idx;

	}
}

NODE_STATE RandomPatternNode2::OnUpdate()
{
	return m_pChildren[m_iSelect]->Update();
}

void RandomPatternNode2::OnStop()
{
}

MoveNode2::MoveNode2(Object* owner, Vec2 endPos, float speed)
	: m_pOwner(owner)
	, m_vEndPos(endPos)
	, m_fSpeed(speed)
{
}

MoveNode2::~MoveNode2()
{
}

void MoveNode2::OnStart()
{
}

NODE_STATE MoveNode2::OnUpdate()
{
	if (m_pOwner == nullptr)
		return NODE_STATE::FAILURE;

	Vec2 pos = m_pOwner->GetPos();

	float dist = (m_vEndPos - pos).Length();
	if (dist < 0.5f)
	{
		return NODE_STATE::SUCCESS;
	}

	Vec2 dir = (m_vEndPos - pos).Normalize();
	pos.x += dir.x * m_fSpeed * fDT;
	pos.y += dir.y * m_fSpeed * fDT;

	m_pOwner->SetPos(pos);

	return NODE_STATE::RUNNING;
}

void MoveNode2::OnStop()
{
}

Boss2Pattern1Node::Boss2Pattern1Node(Object* owner, Object* target)
	: m_pOwner(owner)
	, m_pTarget(target)
	, m_fCurTime(0.f)
	, m_fSpawnTime(0)
	, m_fDangerDelay(0.5f)
	, m_fDelaySpikeSpawn(0.1f)
	, m_fWaitSpikeDelete(4.5f)
	, m_isRight(false)
{
}

Boss2Pattern1Node::~Boss2Pattern1Node()
{
}

void Boss2Pattern1Node::OnStart()
{
	m_fCurTime = 0;

	m_isRight = m_pOwner->GetPos().x > (WINDOW_WIDTH / 2);

	Spike* pSpike = new Spike(m_fWaitSpikeDelete);
	SceneMgr::GetInst()->GetCurScene()->AddObject(pSpike, OBJECT_GROUP::OBJ);
}

NODE_STATE Boss2Pattern1Node::OnUpdate()
{
	m_fCurTime += fDT;
	m_fSpawnTime += fDT;

	if (m_fCurTime >= 6.f)
		return NODE_STATE::SUCCESS;

	if (m_fSpawnTime >= 1)
	{
		m_fSpawnTime = 0;
		SpawnObject();
	}

	return NODE_STATE::RUNNING;
}

void Boss2Pattern1Node::OnStop()
{
}

void Boss2Pattern1Node::SpawnObject()
{
	float speed = (m_isRight ? -300 : 300);
	int wUp = (m_isRight ? 0 : WINDOW_WIDTH);
	int wDown = (m_isRight ? WINDOW_WIDTH : 0);


	DefaultMonster* pJDBlock = new DefaultMonster;
	pJDBlock->GetRigidbody2D()->SetUseGravity(false);
	pJDBlock->GetRigidbody2D()->SetVelocity(Vec2(-speed, 0.f));
	pJDBlock->SetPos({ wUp, 64 * 4 });
	pJDBlock->SetBlock((Vec2(32.f, 32.f)));
	SceneMgr::GetInst()->GetCurScene()->AddObject(pJDBlock, OBJECT_GROUP::OBJ);

	DefaultMonster* pJDBlock2 = new DefaultMonster;
	pJDBlock2->GetRigidbody2D()->SetUseGravity(false);
	pJDBlock2->GetRigidbody2D()->SetVelocity(Vec2(speed, 0.f));
	pJDBlock2->SetPos({ wDown , 64 * 6 });
	pJDBlock2->SetBlock((Vec2(32.f, 32.f)));
	SceneMgr::GetInst()->GetCurScene()->AddObject(pJDBlock2, OBJECT_GROUP::OBJ);
}


Boss2Pattern2Node::Boss2Pattern2Node(Object* owner, Object* target)
	: m_pOwner(owner)
	, m_pTarget(target)
	, m_fShootDelay(0.3f)
	, m_iBulletCount(5)
	, m_iCurShootCount(0)
	, m_fCurTime(0.f)
{
}

Boss2Pattern2Node::~Boss2Pattern2Node()
{
}

void Boss2Pattern2Node::OnStart()
{
	m_fCurTime = 0;
	m_iCurShootCount = 0;
}

NODE_STATE Boss2Pattern2Node::OnUpdate()
{
	m_fCurTime += fDT;

	if (m_iCurShootCount <= m_iBulletCount)
	{
		if (m_fCurTime >= m_fShootDelay)
		{
			m_fCurTime = 0;
			m_iCurShootCount++;
			SpawnBullet();

			if (m_iCurShootCount == m_iBulletCount / 2)
				SpawnObject();
		}
	}

	if (m_iCurShootCount > m_iBulletCount)
		return NODE_STATE::SUCCESS;

	return NODE_STATE::RUNNING;
}

void Boss2Pattern2Node::OnStop()
{
}

void Boss2Pattern2Node::SpawnBullet()
{
	if (m_pTarget == nullptr)
		return;

	ResMgr::GetInst()->Play(L"Bullet");

	Vec2 targetPos = m_pTarget->GetPos();
	Vec2 pos = m_pOwner->GetPos();
	Vec2 dir[3] = { Vec2(-1.5f,0.f), Vec2(1.5f,0.f) };


	dir[0].x += .25f * m_iCurShootCount;
	dir[0].y += .25f * m_iCurShootCount;

	dir[1].x -= .25f * m_iCurShootCount;
	dir[1].y += .25f * m_iCurShootCount;

	for (int i = 0; i < 2; i++)
	{
		dir[i].Normalize();

		Bullet* bullet = new Bullet;
		bullet->SetPos(pos);
		bullet->GetRigidbody2D()->SetVelocity(dir[i] * 400.f);
		SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
	}
}

void Boss2Pattern2Node::SpawnObject()
{
	DefaultMonster* pJDBlock = new DefaultMonster;
	pJDBlock->GetRigidbody2D()->SetVelocity(Vec2(300.f, 50.f));
	pJDBlock->SetPos({ 0, WINDOW_HEIGHT / 2 });
	pJDBlock->SetBlock((Vec2(32.f, 32.f)));
	SceneMgr::GetInst()->GetCurScene()->AddObject(pJDBlock, OBJECT_GROUP::OBJ);

	DefaultMonster* pJDBlockBounce = new DefaultMonster;
	pJDBlockBounce->GetRigidbody2D()->SetVelocity(Vec2(-300.f, 50.f));
	pJDBlockBounce->SetPos({ WINDOW_WIDTH, WINDOW_HEIGHT / 2 });
	pJDBlockBounce->SetBlock((Vec2(32.f, 32.f)));
	SceneMgr::GetInst()->GetCurScene()->AddObject(pJDBlockBounce, OBJECT_GROUP::OBJ);
}

Boss2Pattern3Node::Boss2Pattern3Node(Object* owner, Object* target)
	: m_fCurTime(0.f)
	, m_bSpawn(false)
	, m_iSpawnCount(0)
{
}

Boss2Pattern3Node::~Boss2Pattern3Node()
{
}

void Boss2Pattern3Node::OnStart()
{
	m_fCurTime = 0;
	m_iSpawnCount = 0;
	m_bSpawn = false;
}

NODE_STATE Boss2Pattern3Node::OnUpdate()
{
	m_fCurTime += fDT;

	if (m_fCurTime >= 0.5f && !m_bSpawn)
	{
		SpawnObject();
		m_bSpawn = true;
		m_iSpawnCount++;
	}
	if (m_fCurTime >= 1.f)
	{
		SpawnObject();
		m_fCurTime = 0;
		m_iSpawnCount++;
		m_bSpawn = false;
	}

	if (m_iSpawnCount >= 10)
		return NODE_STATE::SUCCESS;

	return NODE_STATE::RUNNING;
}

void Boss2Pattern3Node::OnStop()
{
}

void Boss2Pattern3Node::SpawnObject()
{
	int x = (m_bSpawn ? 0 : WINDOW_WIDTH);
	float speed = (m_bSpawn ? 500 : -500);
	//if (m_bSpawn) x = WINDOW_WIDTH / 2 - 120;
	//else x = WINDOW_WIDTH / 2 + 240;
	speed += m_fCurTime;

	DefaultMonster* pJDBlock = new DefaultMonster;
	pJDBlock->GetRigidbody2D()->SetUseGravity(false);
	pJDBlock->GetRigidbody2D()->SetVelocity(Vec2(speed, 10.f));
	pJDBlock->SetPos({ x, WINDOW_HEIGHT });
	pJDBlock->SetBlock((Vec2(32.f, 32.f)));
	pJDBlock->SetSpeed(speed);
	SceneMgr::GetInst()->GetCurScene()->AddObject(pJDBlock, OBJECT_GROUP::OBJ);

	DefaultMonster* pJDBlockBounce = new DefaultMonster;
	pJDBlockBounce->GetRigidbody2D()->SetVelocity(Vec2(-speed, 0.f));
	pJDBlockBounce->SetPos({ x, 0 });
	pJDBlockBounce->SetBlock((Vec2(32.f, 32.f)));
	pJDBlockBounce->SetSpeed(speed);
	SceneMgr::GetInst()->GetCurScene()->AddObject(pJDBlockBounce, OBJECT_GROUP::OBJ);
}
