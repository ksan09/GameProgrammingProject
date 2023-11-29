#include "pch.h"
#include "HitEffect.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "Animator.h"

HitEffect::HitEffect()
	: m_fDeleteTime(0.3f)
	, m_fCurTime(0)
	, m_isDie(false)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"HitEffect", L"Texture\\Effect.bmp");

	float size = 80.f;
	CreateAnimator();
	GetAnimator()->CreateAnim(L"HitEffect", m_pTex,
		{0.f, 0.f}, {size, size+2.f}, {size, 0.f}, 6, 0.05f);
	GetAnimator()->PlayAnim(L"HitEffect", false);
}

HitEffect::~HitEffect()
{
}

void HitEffect::Update()
{
	m_fCurTime += fDT;
	if (m_isDie == false && m_fCurTime >= m_fDeleteTime)
	{
		m_isDie = true;
		EventMgr::GetInst()->DeleteObject(this);
	}
	GetAnimator()->Update();
}

void HitEffect::Render(HDC _dc)
{
	Component_Render(_dc);
}
