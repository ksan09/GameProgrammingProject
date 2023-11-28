#include "pch.h"
#include "FallingBlock.h"
#include "Rigidbody2D.h"
#include "GroundCollider.h"
#include "SceneMgr.h"
#include "Scene.h"

FallingBlock::FallingBlock()
{
	SetName(L"FallingBlock");
	CreateRigidbody2D();

	GroundCollider* m_pBottomCol = new GroundCollider;
	m_pBottomCol->SetCollider(this, { 28, 6 }, { 4, 16 });
	SceneMgr::GetInst()->GetCurScene()->AddObject(m_pBottomCol, OBJECT_GROUP::BOTTOM_COL);
}

FallingBlock::~FallingBlock()
{
}

void FallingBlock::Update()
{
	GetRigidbody2D()->LateUpdate();
}
