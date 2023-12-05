#include "pch.h"
#include "Danger.h"
#include "TimeMgr.h"
#include "EventMgr.h"

Danger::Danger()
	: m_fCurTime(0)
	, m_fDeleteDelay(1)
	, m_isDie(false)
{
}

Danger::~Danger()
{
}

void Danger::Update()
{
	m_fCurTime += fDT;
	if (m_isDie == false && m_fCurTime >= m_fDeleteDelay)
	{
		m_isDie = true;
		EventMgr::GetInst()->DeleteObject(this);
	}
}

void Danger::Render(HDC _dc)
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

	Vec2 vPos = Vec2(WINDOW_WIDTH / 2.f + 4, WINDOW_HEIGHT - 160.f);
	Vec2 vScale = Vec2(96, 96);

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
