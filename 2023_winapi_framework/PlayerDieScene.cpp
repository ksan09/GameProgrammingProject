#include "pch.h"
#include "define.h"
#include "Core.h"
#include "playerDieScene.h"
#include "KeyMgr.h"
#include "EventMgr.h"

PlayerDieScene::PlayerDieScene()
	:m_iFontSize(50)
{
}

PlayerDieScene::~PlayerDieScene()
{
}

void PlayerDieScene::Init()
{
}

void PlayerDieScene::Update()
{
	if (KEY_DOWN(KEY_TYPE::SPACE))
	{
		
		EventMgr::GetInst()->SceneChange(L"StageSelect_Scene");
	}
}

void PlayerDieScene::Render(HDC _dc)
{
	HWND hWnd = Core::GetInst()->GetHwnd();
	ReStart(_dc, hWnd);
}

void PlayerDieScene::ReStart(HDC _dc, HWND hWnd)
{
	COLORREF bgColor = RGB(0, 0, 0);
	//FillRect(Core::GetInst()->GetMainDC(), &ps.rcPaint, hBrush);
	RECT rect;
	HBRUSH  g_hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	GetClientRect(hWnd, &rect);

	// 배경 색상으로 채우기
	FillRect(_dc, &rect, g_hbrBackground);
	//Restart
	SetTextColor(_dc, RGB(255, 255, 255));
	SetBkMode(_dc, 1);
	HFONT hFont = CreateFont(m_iFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"DungGeunMo.ttf");
	HFONT hDefaultFont = (HFONT)SelectObject(_dc, hFont);
	RECT restartRect;
	GetClientRect(hWnd, &restartRect);
	DrawText(_dc, L"space바 입력 시 재시작", -1, &restartRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	SelectObject(_dc, hDefaultFont);

	SetTextColor(_dc, RGB(0, 0, 0));
	DeleteObject(g_hbrBackground);
	DeleteObject(hFont);

	
}