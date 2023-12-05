#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Rigidbody2D.h"
#include "Animator.h"
#include "Collider.h"
#include "EventMgr.h"

Bullet::Bullet()
	: m_pTex(nullptr)
	, m_isDie(false)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Bullet", L"Texture\\Bullet.bmp");

	CreateRigidbody2D();
	GetRigidbody2D()->SetUseGravity(false);

	CreateAnimator();
	GetAnimator()->CreateAnim(L"BulletIdle", m_pTex, 
		Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(32.f, 0.f), 7, 0.1f);
	GetAnimator()->PlayAnim(L"BulletIdle", true);

	SetName(L"DamageObject");
	CreateCollider();
	GetCollider()->SetScale({ 16.f, 16.f });
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	GetAnimator()->Update();
	GetRigidbody2D()->LateUpdate();

	if (m_isDie) return;

	Vec2 pos = GetPos();
	float correctVal = 32.f;

	if (pos.x < 0 - correctVal || pos.x > WINDOW_WIDTH + correctVal
		|| pos.y < 0 - correctVal || pos.y > WINDOW_HEIGHT + correctVal)
	{
		EventMgr::GetInst()->DeleteObject(this);

		m_isDie = true;
	}
}

void Bullet::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Bullet::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	wstring objName = pOtherObj->GetName();

	if (!m_isDie && (objName == L"Block" || objName == L"Ground"
		|| objName == L"Player"))
	{
		m_isDie = true;
		EventMgr::GetInst()->DeleteObject(this);
	}
}
