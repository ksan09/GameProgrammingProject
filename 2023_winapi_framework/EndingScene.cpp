#include "pch.h"
#include "EndingScene.h"
#include "Core.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "KeyMgr.h"
#include "ResMgr.h"

EndingScene::EndingScene()
	:m_iFontSize(50)
	, idxNum(10)
	, x(0)
	, y(0.f)
	, saveY(0.f)
	, strArr({ L"제작", L"박우혁 - 개발", L"박성빈 - 개발", L"강산 - 개발, 아트, 기획", L"플레이 해주셔서 감사합니다.", L" ",L" ",  L"The End" })
{
}

EndingScene::~EndingScene()
{
}

void EndingScene::Init()
{
	// 사운드 세팅
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::BGM, 1.f);
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, 0.6f);
	ResMgr::GetInst()->LoadSound(L"Victory", L"Sound\\Victory.wav", true);
	ResMgr::GetInst()->Play(L"Victory");

	HWND hWnd = Core::GetInst()->GetHwnd();

	RECT rect;
	GetClientRect(hWnd, &rect);
	x = rect.right / 2; // 가로 중앙
	y = -3000;
}

void EndingScene::Update()
{
	if (y >= 0)
	{
		saveY = 0;
		y = 0;

		if (KEY_PRESS(KEY_TYPE::SPACE))
			EventMgr::GetInst()->SceneChange(L"Start_Scene");
	}
	else
			y += 0.2f;
}

void EndingScene::Render(HDC _dc)
{
	//TextOut();
	SetTextColor(_dc, RGB(255, 255, 255));
	HFONT hFont = CreateFont(m_iFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, L"DungGeunMo");
	SelectObject(_dc, hFont); 
	AddFontResourceW(L"Font\\DungGeunMo.ttf");
	HWND hWnd = Core::GetInst()->GetHwnd();
	RECT rect;
	RECT rectBackGround;
	HBRUSH  g_hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	GetClientRect(hWnd, &rectBackGround);

	// 배경 색상으로 채우기
	FillRect(_dc, &rectBackGround, g_hbrBackground);


	GetClientRect(hWnd, &rect);

	saveY = y;

	for (int i = strArr.size() - 1; i >= 0; i--)
	{
		rect.top = saveY; // y 값을 반영하여 텍스트의 시작 위치를 조정
		DrawText(_dc, strArr[i].c_str(), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		saveY += 300;
		idxNum = i;
	}

	DeleteObject(hFont);
	DeleteObject(hWnd);
	DeleteObject(g_hbrBackground);
}
