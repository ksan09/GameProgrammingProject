#include "pch.h"
#include "AutoBullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Rigidbody2D.h"
#include "Animator.h"
#include "Collider.h"
#include "EventMgr.h"

AutoBullet::AutoBullet(Object* target)
	: m_pTarget(target)
	, m_fCurTime(0)
	, m_fDeleteTime(0)
	, m_fTargetingTime(0.5f)
	, m_isTargeting(false)
{
}

AutoBullet::~AutoBullet()
{
}

void AutoBullet::Update()
{
	// 방향 계산
	// Alpha = 0.1
	// A * (1 - Alpha) + B * Alpha
	m_fCurTime += fDT;
	if (m_isTargeting == false)
	{
		if (m_fTargetingTime < m_fCurTime)
		{
			m_isTargeting = true;
			m_fCurTime = 0;
		}
	}
	else if (m_fCurTime >= 0.033f && m_fDeleteTime < 1.5f)
	{
		m_fDeleteTime += m_fCurTime;
		m_fCurTime = 0.f;

		Vec2 velo = GetRigidbody2D()->GetVelocity();
		Vec2 dir = velo.Normalize();

		Vec2 pos = GetPos();
		Vec2 targetPos = m_pTarget->GetPos();
		Vec2 lookDir = (targetPos - pos).Normalize();

		float Alpha = 0.1f;
		Vec2 fixDir = Vec2(dir.x * (1 - Alpha) + lookDir.x * Alpha, dir.y * (1 - Alpha) + lookDir.y * Alpha);
		GetRigidbody2D()->SetVelocity(fixDir * 500.f);
	}

	GetAnimator()->Update();
	GetRigidbody2D()->LateUpdate();

	if (m_isDie) return;

	Vec2 pos = GetPos();
	float correctVal = 32.f;

	if (pos.x < 0 - correctVal || pos.x > WINDOW_WIDTH + correctVal
		|| pos.y > WINDOW_HEIGHT + correctVal)
	{
		EventMgr::GetInst()->DeleteObject(this);
		m_isDie = true;
	}
}
