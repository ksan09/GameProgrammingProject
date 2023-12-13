#include "pch.h"
#include "BulletMonster.h"
#include "Collider.h"
#include "EventMgr.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "Rigidbody2D.h"
#include "BoundGroundCollider.h"
#include "Bullet.h"

BulletMonster::BulletMonster()
	: m_fCurTime(0.f)
	, m_fSpawnTime(.55f)
	, m_isDie(false)
	, m_bDir()
	, m_speed(100.f)
	, m_pBottomCol(nullptr)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"DefaultMonster", L"Texture\\DefaultMonster.bmp");
	SetName(L"DamageAndJumpAbleObject");

	m_pBottomCol = new BoundGroundCollider;
	m_pBottomCol->SetCollider(this, { 28, 6 }, { 4, 16 });
	SceneMgr::GetInst()->GetCurScene()->AddObject(m_pBottomCol, OBJECT_GROUP::BOTTOM_COL);

	CreateRigidbody2D();
}

BulletMonster::~BulletMonster()
{
}

void BulletMonster::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj == m_pBottomCol)
		return;

	wstring objName = pOtherObj->GetName();
	// Block
	if (objName == L"DamageAndJumpAbleObject")
	{
		return;
	}

	if (objName == L"Block")
	{
		GetRigidbody2D()->StopVeloX();
	}
	else if (objName == L"DIR_BOTTOM_COL" && m_isDie == false)
	{
		m_isDie = true;
		EventMgr::GetInst()->DeleteObject(this);
		EventMgr::GetInst()->DeleteObject(m_pBottomCol);
	}
}

void BulletMonster::ExitCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj == m_pBottomCol)
		return;

	wstring objName = pOtherObj->GetName();
	// Block
	if (objName == L"DamageAndJumpAbleObject")
	{
		return;
	}

	if (objName == L"Block")
	{
		GetRigidbody2D()->SetVelocity(
			{ m_speed, GetRigidbody2D()->GetVelocity().y });
	}
}

void BulletMonster::Update()
{
	GetRigidbody2D()->LateUpdate();

	m_fCurTime += fDT;

	if (m_fCurTime >= m_fSpawnTime)
	{
		m_fSpawnTime = 3;
		m_fCurTime = 0;
		SpawnBullet();
	}
}

void BulletMonster::SpawnBullet()
{
	m_bDir = !m_bDir;

	ResMgr::GetInst()->Play(L"Bullet");
	Vec2 crossDir[4] = { Vec2(1,0), Vec2(0,1) ,Vec2(-1,0) , Vec2(0,-1) };
	Vec2 slantCrossDir[4] = { Vec2(1,1), Vec2(-1,1), Vec2(-1,-1), Vec2(1,-1) };

	for (int i = 0; i < 4; i++)
	{
		Bullet* bullet = new Bullet;
		bullet->SetPos(this->GetPos());
		if (m_bDir)
			bullet->GetRigidbody2D()->SetVelocity(crossDir[i] * 300.f);
		else
			bullet->GetRigidbody2D()->SetVelocity(slantCrossDir[i] * 300.f);
		SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::OBJ);
	}
}
