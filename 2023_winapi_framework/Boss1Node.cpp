#include "pch.h"
#include "Boss1Node.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "DefaultMonster.h"
#include "Spike.h"
#include "Bullet.h"
#include "Boss1.h"
#include "Core.h"
#include "WarningObject.h"
#include "ResMgr.h"
#include <cmath>


RandomPatternNode1::RandomPatternNode1()
	: m_iSelect(0)
{
}

RandomPatternNode1::~RandomPatternNode1()
{
}

void RandomPatternNode1::OnStart()
{

}

NODE_STATE RandomPatternNode1::OnUpdate()
{
	return m_pChildren[m_iSelect % m_pChildren.size()]->Update();
}

void RandomPatternNode1::OnStop()
{
}

BoundMonsterSpawnPattern1Node1::BoundMonsterSpawnPattern1Node1(Object* owner, Object* target)
	: m_pOwner(owner)
	, m_pTarget(target)
	, m_isRight(false)
	, m_isDanger(false)
	, m_fDangerDelay(1.f)
	, m_fCurTime(0.f)
	, m_fCurTime2(0.f)
	, m_fSpawnDelay(0.5f)
	, m_iCurSpawnCount(0)
	, m_iSpawnCount(10)
	, m_fDelayTime(3.f)
	, m_fSpawnMonsterSpeed(200.f)
{
}

BoundMonsterSpawnPattern1Node1::~BoundMonsterSpawnPattern1Node1()
{
}

void BoundMonsterSpawnPattern1Node1::OnStart()
{
	m_fCurTime = 0;
	m_iCurSpawnCount = 0;

	m_isRight = m_pOwner->GetPos().x > (WINDOW_WIDTH / 2);

	WarningObject* pWarning = new WarningObject(1.5f);
	SceneMgr::GetInst()->GetCurScene()->AddObject(pWarning, OBJECT_GROUP::OBJ);
}

NODE_STATE BoundMonsterSpawnPattern1Node1::OnUpdate()
{
	m_fCurTime2 += fDT;
	m_fCurTime += fDT;
	if (m_fCurTime >= m_fSpawnDelay)
	{
		m_fCurTime = 0;
		SpawnBullet();
	}

	if (m_fCurTime2 >= m_fDelayTime)
	{
		m_fCurTime2 = 0;
		return NODE_STATE::SUCCESS;
	}

	return NODE_STATE::RUNNING;
}

void BoundMonsterSpawnPattern1Node1::OnStop()
{
}

void BoundMonsterSpawnPattern1Node1::SpawnObject()
{
	/*float speed = (m_isRight ? -m_fSpawnMonsterSpeed : m_fSpawnMonsterSpeed);

	DefaultMonster* pJDBlock = new DefaultMonster;
	pJDBlock->SetPos(m_pOwner->GetPos());
	pJDBlock->SetBlock((Vec2(32.f, 32.f)));
	pJDBlock->GetRigidbody2D()->SetVelocity({ speed, -10.f });
	pJDBlock->SetSpeed(speed);
	SceneMgr::GetInst()->GetCurScene()->AddObject(pJDBlock, OBJECT_GROUP::OBJ);*/
}

void BoundMonsterSpawnPattern1Node1::SpawnBullet()
{
	if (m_pTarget == nullptr)
		return;

	ResMgr::GetInst()->Play(L"Bullet");
	Vec2 pos = m_pOwner->GetPos();
	pos.y -= 30;

	Vec2 targetPos1 = { 0.f, pos.y };
	Vec2 dir = (targetPos1 - pos);
	dir.Normalize();

	Vec2 targetPos2 = { 1000.f, pos.y };
	Vec2 dir2 = (targetPos2 - pos);
	dir2.Normalize();

	Bullet* bullet = new Bullet;
	bullet->SetPos(pos);
	bullet->GetRigidbody2D()->SetVelocity(dir * 500.f);
	SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);

	Bullet* bullet2 = new Bullet;
	bullet2->SetPos(pos);
	bullet2->GetRigidbody2D()->SetVelocity(dir2 * 500.f);
	SceneMgr::GetInst()->GetCurScene()->AddObject(bullet2, OBJECT_GROUP::OBJ);
}

JumpNode::JumpNode(Object* owner, Object* endPos, float speed)
	: m_pOwner(owner)
	, m_vEndPos(endPos)
	, m_fSpeed(speed)
	, m_fCurTime(0)
	, m_fDis(0)
	, m_pRb(NULL)
{

}

JumpNode::~JumpNode()
{
}

void JumpNode::OnStart()
{

	m_pRb = m_pOwner->GetRigidbody2D();

	if (m_pRb == NULL)
	{
		//m_pOwner->SetPos({ 200, 100 });
		return;
	}

	Vec2 vVelo = m_pRb->GetVelocity();
	m_pRb->SetVelocity({ vVelo.x, -800.f });


	ResMgr::GetInst()->Play(L"Jump");
}

NODE_STATE JumpNode::OnUpdate()
{


	m_fDis = m_vEndPos->GetPos().x - m_pOwner->GetPos().x;

	if (m_fDis <= 0)
	{
		float x = m_pOwner->GetPos().x - 0.15f;
		m_pOwner->SetPos({ x ,m_pOwner->GetPos().y });
	}
	else if (m_fDis > 0)
	{
		float x = m_pOwner->GetPos().x + 0.15f;
		m_pOwner->SetPos({ x ,m_pOwner->GetPos().y });
	}

	m_pRb = m_pOwner->GetRigidbody2D();
	Vec2 velo = m_pRb->GetVelocity();

	if (velo.y == 0)
	{
		m_pRb = NULL;
		return NODE_STATE::SUCCESS;
	}

	return NODE_STATE::RUNNING;
}

void JumpNode::OnStop()
{
}

Boss1Pattern2Node::Boss1Pattern2Node(Object* _Owner, Object* _target)
	: m_fDangerDelay(1.f)
	, m_fDelaySpikeSpawn(0.1f)
	, m_fWaitSpikeDelete(4.5f)
	, m_fCurTime(0.f)
	, m_pOwner(_Owner)
	, m_pTarget(_target)
	, m_pSaveOwner(nullptr)
{
}

Boss1Pattern2Node::~Boss1Pattern2Node()
{
}

void Boss1Pattern2Node::OnStart()
{
	m_fCurTime = 0;
	m_pSaveOwner = m_pOwner;
	OnShoot();
}

NODE_STATE Boss1Pattern2Node::OnUpdate()
{
	m_fCurTime += fDT;
	if (m_fCurTime >= 1.5f)
	{
		return NODE_STATE::SUCCESS;
	}

	return NODE_STATE::RUNNING;
}

void Boss1Pattern2Node::OnStop()
{
}

void Boss1Pattern2Node::OnShoot()
{
	ResMgr::GetInst()->Play(L"Bullet");
	int numBullets = 10;
	float angle = -(180.0f / numBullets);

	for (int i = 0; i < numBullets; ++i)
	{
		Vec2 pos = m_pOwner->GetPos();

		float radians = (angle * i) * (3.141592653f / 180.0f);

		pos.x += cosf(radians) * 100.0f;
		pos.y += sinf(radians) * 100.0f;

		Bullet* bullet = new Bullet;
		bullet->SetPos(pos);
		bullet->GetRigidbody2D()->SetVelocity(Vec2(cosf(radians), sinf(radians)) * 400.0f);

		SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
	}
}

