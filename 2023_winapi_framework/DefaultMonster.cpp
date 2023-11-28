#include "pch.h"
#include "DefaultMonster.h"
#include "Collider.h"
#include "EventMgr.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "Rigidbody2D.h"
#include "BoundGroundCollider.h"

DefaultMonster::DefaultMonster()
	: m_isDie(false)
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

DefaultMonster::~DefaultMonster()
{
}

void DefaultMonster::EnterCollision(Collider* _pOther)
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

void DefaultMonster::ExitCollision(Collider* _pOther)
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
			{ m_speed, GetRigidbody2D()->GetVelocity().y});
	}
}

void DefaultMonster::Update()
{
	GetRigidbody2D()->LateUpdate();
}
