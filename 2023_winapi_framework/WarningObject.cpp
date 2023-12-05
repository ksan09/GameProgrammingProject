#include "pch.h"
#include "WarningObject.h"
#include "TimeMgr.h"
#include "Core.h"
#include "EventMgr.h"

WarningObject::WarningObject(float deleteTime)
	: m_fDangerDelay(1.f)
	, m_fDeleteDelay(deleteTime)
	, m_fCurTime(0)
	, m_isDie(false)
	, m_isDanger(true)
	, m_isDangerEnd(false)
{
}

WarningObject::~WarningObject()
{
}

void WarningObject::Update()
{
	m_fCurTime += fDT;
	if (m_isDanger && m_fCurTime >= m_fDangerDelay)
	{
		m_isDanger = false;
		m_fCurTime = 0;

	}

	else if (m_isDanger == false && m_isDangerEnd == false
		&& m_fCurTime >= 0.25f)
	{
		m_isDangerEnd = true;
		m_fCurTime = 0;
	}

	if (m_isDangerEnd == false) return;

	if (!m_isDie && m_fDeleteDelay <= m_fCurTime)
	{
		m_fCurTime = 0;
		m_isDie = true;
	}
	else if (m_isDie && m_fCurTime >= 0.25f)
	{
		m_fCurTime = 0;
		EventMgr::GetInst()->DeleteObject(this);
	}
}

void WarningObject::Render(HDC _dc)
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

		Vec2 vPos = Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 125);
		Vec2 vScale = Vec2(WINDOW_WIDTH, 35);

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
