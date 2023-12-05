#include "pch.h"
#include "Spike.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "EventMgr.h"
#include "Animator.h"
#include "Collider.h"
#include "Core.h"

Spike::Spike(float deleteTime)
	: m_fDangerDelay(1.f)
	, m_fDeleteDelay(deleteTime)
	, m_fCurTime(0)
	, m_isDie(false)
	, m_isDanger(true)
	, m_isDangerEnd(false)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Spike", L"Texture\\Spike.bmp");
	
	CreateAnimator();
	GetAnimator()->CreateAnim(L"Spike_Up", m_pTex, Vec2(0.f, 0.f),
		Vec2(960.f, 96.f), Vec2(0.f, 96.f), 5, 0.05f);
	GetAnimator()->CreateAnim(L"Spike_Down", m_pTex, Vec2(0.f, 96.f * 4),
		Vec2(960.f, 96.f), Vec2(0.f, -96.f), 5, 0.05f);
	//
	GetAnimator()->PlayAnim(L"Spike_Down", false);

	SetPos(Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 156));
	SetName(L"DamageObject");
}

Spike::~Spike()
{
}

void Spike::Update()
{
	m_fCurTime += fDT;
	if (m_isDanger && m_fCurTime >= m_fDangerDelay)
	{
		m_isDanger = false;
		m_fCurTime = 0;

		Core::GetInst()->Shake(0.15f, 2.f);

		CreateCollider();
		SetScale(Vec2(WINDOW_WIDTH, 96 - 16));
		GetCollider()->SetOffSetPos({ 0, 80 });
		GetCollider()->SetScale(Vec2(WINDOW_WIDTH, 96 - 80));

		ResMgr::GetInst()->Play(L"SpikeUp");
		GetAnimator()->PlayAnim(L"Spike_Up", false);
	}
	else if (m_isDanger == false && m_isDangerEnd == false
		&& m_fCurTime >= 0.25f)
	{
		m_isDangerEnd = true;
		m_fCurTime = 0;

		GetCollider()->SetOffSetPos({ 0, 16 });
		GetCollider()->SetScale(Vec2(WINDOW_WIDTH, 96 - 16));
	}

	if (m_isDangerEnd == false) return;

	GetAnimator()->Update();
	if (!m_isDie && m_fDeleteDelay <= m_fCurTime)
	{
		m_fCurTime = 0;
		m_isDie = true;
		GetAnimator()->PlayAnim(L"Spike_Down", false);
	}
	else if (m_isDie && m_fCurTime >= 0.25f)
	{
		m_fCurTime = 0;
		EventMgr::GetInst()->DeleteObject(this);
	}
}

void Spike::Render(HDC _dc)
{
	if (m_isDanger)
	{
		HDC hAlphaDC = CreateCompatibleDC(_dc);
		HBITMAP hAlphaBit = CreateCompatibleBitmap(_dc, WINDOW_WIDTH, WINDOW_HEIGHT);
		SelectObject(hAlphaDC, hAlphaBit);

		BitBlt(hAlphaDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			_dc, 0, 0, SRCCOPY);

		HBRUSH hDangerColorBrush = CreateSolidBrush(RGB(255, 0, 0));
		HPEN hDangerColorPen = CreatePen(PS_NULL, 0, RGB(255, 0, 0));
		SelectObject(hAlphaDC, hDangerColorBrush);
		SelectObject(hAlphaDC, hDangerColorPen);
		
		Vec2 vPos = Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 150);
		Vec2 vScale = Vec2(WINDOW_WIDTH, 96);

		static BLENDFUNCTION bf;
		bf.SourceConstantAlpha = 180;
		
		RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, hAlphaDC);

		AlphaBlend(_dc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			hAlphaDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, bf);

		DeleteObject(hDangerColorBrush);
		DeleteObject(hDangerColorPen);
		DeleteObject(hAlphaBit);
		DeleteDC(hAlphaDC);
	}
	else
	{
		Component_Render(_dc);
	}
}
