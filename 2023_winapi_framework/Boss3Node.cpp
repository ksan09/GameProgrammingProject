#include "pch.h"
#include "Boss3Node.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "DefaultMonster.h"
#include "Spike.h"
#include "Bullet.h"
#include "ResMgr.h"

RandomPatternNode::RandomPatternNode()
	: m_iSelect(-1)
{
}

RandomPatternNode::~RandomPatternNode()
{
}

void RandomPatternNode::OnStart()
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

NODE_STATE RandomPatternNode::OnUpdate()
{
	return m_pChildren[m_iSelect]->Update();
}

void RandomPatternNode::OnStop()
{
}

BoundMonsterSpawnPattern1Node::BoundMonsterSpawnPattern1Node(Object* owner, Object* target)
	: m_pOwner(owner)
	, m_pTarget(target)
	, m_isRight(false)
	, m_fCurTime(0.f)
	, m_fSpawnDelay(0.5f)
	, m_iCurSpawnCount(0)
	, m_iSpawnCount(10)
	, m_fDelayTime(3.f)
	, m_fSpawnMonsterSpeed(200.f)
{
}

BoundMonsterSpawnPattern1Node::~BoundMonsterSpawnPattern1Node()
{
}

void BoundMonsterSpawnPattern1Node::OnStart()
{
	m_fCurTime = 0;
	m_iCurSpawnCount = 0;

	m_isRight = m_pOwner->GetPos().x > (WINDOW_WIDTH / 2);
}

NODE_STATE BoundMonsterSpawnPattern1Node::OnUpdate()
{
	m_fCurTime += fDT;
	if (m_iCurSpawnCount < m_iSpawnCount && m_fCurTime >= m_fSpawnDelay)
	{
		SpawnObject();
		m_fCurTime = 0;
		m_iCurSpawnCount++;

		if (m_iCurSpawnCount % 5 - 2 == 0)
		{
			SpawnBullet();
		}

	}

	if (m_iCurSpawnCount >= m_iSpawnCount && m_fCurTime >= m_fDelayTime)
	{
		return NODE_STATE::SUCCESS;
	}

	return NODE_STATE::RUNNING;
}

void BoundMonsterSpawnPattern1Node::OnStop()
{
}

void BoundMonsterSpawnPattern1Node::SpawnObject()
{
	float speed = (m_isRight ? -m_fSpawnMonsterSpeed : m_fSpawnMonsterSpeed);

	ResMgr::GetInst()->Play(L"MobShot");
	DefaultMonster* pJDBlock = new DefaultMonster;
	pJDBlock->SetPos(m_pOwner->GetPos());
	pJDBlock->SetBlock((Vec2(32.f, 32.f)));
	pJDBlock->GetRigidbody2D()->SetVelocity({ speed, -10.f });
	pJDBlock->SetSpeed(speed);
	SceneMgr::GetInst()->GetCurScene()->AddObject(pJDBlock, OBJECT_GROUP::OBJ);
}

void BoundMonsterSpawnPattern1Node::SpawnBullet()
{
	if (m_pTarget == nullptr)
		return;

	ResMgr::GetInst()->Play(L"Bullet");

	Vec2 targetPos = m_pTarget->GetPos();
	Vec2 pos = m_pOwner->GetPos();
	Vec2 dir = ( targetPos - pos );
	dir.Normalize();

	Bullet* bullet = new Bullet;
	bullet->SetPos(pos);
	bullet->GetRigidbody2D()->SetVelocity(dir * 300.f);
	SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
}

MoveNode::MoveNode(Object* owner, Vec2 endPos, float speed)
	: m_pOwner(owner)
	, m_vEndPos(endPos)
	, m_fSpeed(speed)
{
}

MoveNode::~MoveNode()
{
}

void MoveNode::OnStart()
{
}

NODE_STATE MoveNode::OnUpdate()
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

void MoveNode::OnStop()
{
}

Boss3Pattern2Node::Boss3Pattern2Node()
	: m_fDangerDelay(1.f)
	, m_fDelaySpikeSpawn(0.1f)
	, m_fWaitSpikeDelete(4.5f)
	, m_fCurTime(0.f)
{
}

Boss3Pattern2Node::~Boss3Pattern2Node()
{
}

void Boss3Pattern2Node::OnStart()
{
	m_fCurTime = 0;
	// 몹들 각자 위치에 소환
	for (int i = 0; i < 4; ++i)
	{
		DefaultMonster* pJDBlock = new DefaultMonster;
		pJDBlock->SetPos({ 128 + i * 240, 128 * 3 });
		pJDBlock->SetBlock((Vec2(32.f, 32.f)));
		SceneMgr::GetInst()->GetCurScene()->AddObject(pJDBlock, OBJECT_GROUP::OBJ);
	}

	Spike* pSpike = new Spike(m_fWaitSpikeDelete);
	SceneMgr::GetInst()->GetCurScene()->AddObject(pSpike, OBJECT_GROUP::OBJ);
}

NODE_STATE Boss3Pattern2Node::OnUpdate()
{
	m_fCurTime += fDT;
	if (m_fCurTime >= 6.f)
		return NODE_STATE::SUCCESS;

	return NODE_STATE::RUNNING;
}

void Boss3Pattern2Node::OnStop()
{
}

Boss3Pattern3Node::Boss3Pattern3Node(Object* owner, Object* target)
	: m_pOwner(owner)
	, m_pTarget(target)
	, m_fCurTime(0.f)
	, m_fShootDelay(0.2f)
	, m_iBulletCount(10)
	, m_iCurShootCount(0)
	, m_bSpikeSpawn(false)
{
}

Boss3Pattern3Node::~Boss3Pattern3Node()
{
}

void Boss3Pattern3Node::OnStart()
{
	m_iCurShootCount = 0;
	m_fCurTime = 0;
	m_bSpikeSpawn = false;
}

NODE_STATE Boss3Pattern3Node::OnUpdate()
{
	m_fCurTime += fDT;

	if (m_iCurShootCount >= m_iBulletCount)
	{
		if (m_bSpikeSpawn == false)
		{
			Spike* pSpike = new Spike(0.2f);
			SceneMgr::GetInst()->GetCurScene()->AddObject(pSpike, OBJECT_GROUP::OBJ);
			m_bSpikeSpawn = true;
		}

		if (m_fCurTime >= 0.3f)
			return NODE_STATE::SUCCESS;

		return NODE_STATE::RUNNING;
	}

	if (m_fCurTime >= m_fShootDelay)
	{
		m_fCurTime = 0;
		m_iCurShootCount++;
		SpawnBullet();
	}

	return NODE_STATE::RUNNING;
}

void Boss3Pattern3Node::OnStop()
{
}

void Boss3Pattern3Node::SpawnBullet()
{
	if (m_pTarget == nullptr)
		return;

	ResMgr::GetInst()->Play(L"Bullet");

	Vec2 targetPos = m_pTarget->GetPos();
	Vec2 pos = m_pOwner->GetPos();
	Vec2 dir = (targetPos - pos);
	dir.Normalize();

	Bullet* bullet = new Bullet;
	bullet->SetPos(pos);
	bullet->GetRigidbody2D()->SetVelocity(dir * 500.f);
	SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
}