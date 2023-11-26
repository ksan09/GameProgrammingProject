#include "pch.h"
#include "GroundCollider.h"
#include "Collider.h"
#include "Rigidbody2D.h"

GroundCollider::GroundCollider()
	: m_pOwner(nullptr)
{
	CreateCollider();
	SetName(L"GroundCheckCol");
}

GroundCollider::~GroundCollider()
{
}

void GroundCollider::EnterCollision(Collider* _pOther)
{
	Rigidbody2D* rb = m_pOwner->GetRigidbody2D();
	if (rb == nullptr)
		return;

	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj == m_pOwner)
		return;

	wstring objName = pOtherObj->GetName();

	if (objName == L"Block" || objName == L"Ground")
	{
		GroundCheck(rb);
	}
}

void GroundCollider::Update()
{
	SetPos(m_pOwner->GetPos());
}

void GroundCollider::SetCollider(Object* owner, Vec2 scale, Vec2 offset)
{
	m_pOwner = owner;

	Collider* col = GetCollider();
	col->SetScale(scale);
	col->SetOffSetPos(offset);
}

void GroundCollider::GroundCheck(Rigidbody2D* rb)
{
	rb->Stop();
	rb->SetUseGravity(false);
}
