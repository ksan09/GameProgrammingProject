#include "pch.h"
#include "EndingScene.h"
#include "Core.h"
#include "TimeMgr.h"

EndingScene::EndingScene()
	:m_iFontSize(50)
	, idxNum(10)
	, x(0)
	, y(0.f)
	, saveY(0.f)
	, strArr({ L"����", L"�ڿ��� - ����", L"�ڼ��� - ����", L"���� - ����, ��Ʈ, ��ȹ", L"�÷��� ���ּż� �����մϴ�.", L" ",L" ",  L"The End" })
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
	x = rect.right / 2; // ���� �߾�
	y = -3000;
}

void EndingScene::Update()
{
	if (y >= 0)
	{
		saveY = 0;
		y = 0;
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

	HWND hWnd = Core::GetInst()->GetHwnd();
	RECT rect;
	RECT rectBackGround;
	HBRUSH  g_hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	GetClientRect(hWnd, &rectBackGround);

	// ��� �������� ä���
	FillRect(_dc, &rectBackGround, g_hbrBackground);


	GetClientRect(hWnd, &rect);

	saveY = y;

	for (int i = strArr.size() - 1; i >= 0; i--)
	{
		rect.top = saveY; // y ���� �ݿ��Ͽ� �ؽ�Ʈ�� ���� ��ġ�� ����
		DrawText(_dc, strArr[i].c_str(), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		saveY += 300;
		idxNum = i;
	}

	DeleteObject(g_hbrBackground);
}
