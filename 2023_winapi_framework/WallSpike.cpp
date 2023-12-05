#include "pch.h"
#include "WallSpike.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "EventMgr.h"
#include "Animator.h"
#include "Collider.h"
#include "Core.h"

WallSpike::WallSpike(float deleteTime, bool isLeft)
	: m_fDangerDelay(1.f)
	, m_fDeleteDelay(deleteTime)
	, m_fCurTime(0)
	, m_isDie(false)
	, m_isDanger(true)
	, m_isDangerEnd(false)
	, m_isLeft(isLeft)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"WallSpike", L"Texture\\WallSpike.bmp");

#pragma region Animator
	float sizeX = 96, sizeY = 640;

	CreateAnimator();
	GetAnimator()->CreateAnim(L"LeftSpike_Up", m_pTex, Vec2(sizeX * 4, 0.f),
		Vec2(sizeX, sizeY), Vec2(-sizeX, 0.f), 5, 0.05f);
	GetAnimator()->CreateAnim(L"LeftSpike_Down", m_pTex, Vec2(0.f, 0.f),
		Vec2(sizeX, sizeY), Vec2(sizeX, 0.f), 5, 0.05f);

	GetAnimator()->CreateAnim(L"RightSpike_Up", m_pTex, Vec2(sizeX * 5, 0.f),
		Vec2(sizeX, sizeY), Vec2(sizeX, 0.f), 5, 0.05f);
	GetAnimator()->CreateAnim(L"RightSpike_Down", m_pTex, Vec2(sizeX * 9, 0.f),
		Vec2(sizeX, sizeY), Vec2(-sizeX, 0.f), 5, 0.05f);
	//
	GetAnimator()->PlayAnim(L"LeftSpike_Up", false);
#pragma endregion

	SetName(L"DamageObject");
}

WallSpike::~WallSpike()
{
}

void WallSpike::Update()
{
	m_fCurTime += fDT;
	if (m_isDanger && m_fCurTime >= m_fDangerDelay)
	{
		m_isDanger = false;
		m_fCurTime = 0;

		Core::GetInst()->Shake(0.15f, 2.f);

		CreateCollider();
		SetScale(Vec2(80, WINDOW_HEIGHT));
		GetCollider()->SetOffSetPos({ (m_isLeft ? -48 : 32) + 6, 0});
		GetCollider()->SetScale(Vec2(16, WINDOW_HEIGHT));

		ResMgr::GetInst()->Play(L"SpikeUp");
		if(m_isLeft)
			GetAnimator()->PlayAnim(L"LeftSpike_Up", false);
		else
			GetAnimator()->PlayAnim(L"RightSpike_Up", false);
	}
	else if (m_isDanger == false && m_isDangerEnd == false
		&& m_fCurTime >= 0.25f)
	{
		m_isDangerEnd = true;
		m_fCurTime = 0;

		GetCollider()->SetOffSetPos({ (m_isLeft ? -16 : 0) + 6, 0 });
		GetCollider()->SetScale(Vec2(80, WINDOW_HEIGHT));
	}

	if (m_isDangerEnd == false) return;

	GetAnimator()->Update();
	if (!m_isDie && m_fDeleteDelay <= m_fCurTime)
	{
		m_fCurTime = 0;
		m_isDie = true;
		if (m_isLeft)
			GetAnimator()->PlayAnim(L"LeftSpike_Down", false);
		else
			GetAnimator()->PlayAnim(L"RightSpike_Down", false);
	}   
	else if (m_isDie && m_fCurTime >= 0.25f)
	{
		m_fCurTime = 0;
		EventMgr::GetInst()->DeleteObject(this);
	}
}

void WallSpike::Render(HDC _dc)
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

		Vec2 vPos = GetPos();
		Vec2 vScale = Vec2(96, WINDOW_HEIGHT);

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
