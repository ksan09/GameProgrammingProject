#include "pch.h"
#include "BoundGroundCollider.h"
#include "Rigidbody2D.h"
#include "EventMgr.h"

BoundGroundCollider::BoundGroundCollider()
	: m_jumpValue(-800.f)
	, m_isDie(false)
{
}

BoundGroundCollider::~BoundGroundCollider()
{
}

void BoundGroundCollider::GroundCheck(Rigidbody2D* rb)
{
	Vec2 velo = rb->GetVelocity();
	rb->SetVelocity({ velo.x, m_jumpValue });
}

void BoundGroundCollider::Update()
{
	// if object exit map, delete object
	SetPos(m_pOwner->GetPos());

	if (m_isDie)
		return;

	Vec2 pos = GetPos();
	float correctVal = max(m_pOwner->GetScale().x, m_pOwner->GetScale().y);

	if (pos.x < 0 - correctVal || pos.x > WINDOW_WIDTH + correctVal
		|| pos.y < 0 - correctVal || pos.y > WINDOW_HEIGHT + correctVal)
	{
		EventMgr::GetInst()->DeleteObject(m_pOwner);
		EventMgr::GetInst()->DeleteObject(this);

		m_isDie = true;
	}
}
