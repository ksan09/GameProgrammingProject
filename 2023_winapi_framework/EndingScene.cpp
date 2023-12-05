#include "pch.h"
#include "EndingScene.h"
#include "Core.h"
#include "TimeMgr.h"

EndingScene::EndingScene()
	:m_fCurTime(0)
	, m_iFontSize(100)
	,idxNum(0)
	, x(0)
	, y(0.f)
	, deltaFontSize(2)
	, windowHeight(640)
	, str(L"")
	, strArr({ L"강산", L"박우혁", L"박성빈", L"The End"})
{
}

EndingScene::~EndingScene()
{
}

void EndingScene::Init()
{
	HWND hWnd = Core::GetInst()->GetHwnd();

	RECT rect;
	GetClientRect(hWnd, &rect);
	x = rect.right / 2; // 가로 중앙
	y = -700;
	str = strArr[idxNum];
}

void EndingScene::Update()
{
	if (y <= 0)
		y += 0.5f;

	if (y >= 0 && idxNum < 3)
	{
		m_fCurTime += fDT;

		if (m_fCurTime >= 1)
		{
			m_fCurTime = 0;
			y =- 600;
			str = strArr[++idxNum];
		}
	}
}

void EndingScene::Render(HDC _dc)
{
	//TextOut();
	SetTextColor(_dc, RGB(0, 0, 0));
	HFONT hFont = CreateFont(m_iFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, L"Arial");
	SelectObject(_dc, hFont);

	HWND hWnd = Core::GetInst()->GetHwnd();
	RECT rect;
	GetClientRect(hWnd, &rect);
	rect.top = y; // y 값을 반영하여 텍스트의 시작 위치를 조정
	DrawText(_dc, str.c_str(), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}
