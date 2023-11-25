#include "pch.h"
#include "Rigidbody2D.h"
#include "TimeMgr.h"
#include "Object.h"

Rigidbody2D::Rigidbody2D()
	: m_useGravity(true)
	, m_gravity(980 + 490.f)
	, m_velocity()
	, m_pOwner(nullptr)
	, m_isFalling(false)
	, m_isGrounded(false)
{
}

Rigidbody2D::~Rigidbody2D()
{
}

void Rigidbody2D::LateUpdate()
{
	FallGravity(); // 중력 작용

	m_isFalling = (m_velocity.y < 0);
	CalculatePos();
}

void Rigidbody2D::GroundCheck()
{
	if (m_velocity.y >= 0)	// 올라가는 중이다.
	{
		m_isGrounded = false;
		return;
	}

	m_isGrounded = true;
}

void Rigidbody2D::FallGravity()
{
	if (m_useGravity == false)
		return;

	if (m_isGrounded == true)
	{
		m_velocity.y = 0;
		return;
	}

	m_velocity.y += m_gravity * fDT;
}

void Rigidbody2D::CalculatePos()
{
	Vec2 pos = m_pOwner->GetPos();
	if(!(m_isStopMoveLeft && m_velocity.x < 0)
		&& !(m_isStopMoveRight && m_velocity.x > 0))
		pos.x += m_velocity.x * fDT;
	pos.y += m_velocity.y * fDT;

	m_pOwner->SetPos(pos);
}
