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
{/*
	if (KEY_DOWN(KEY_TYPE::W) || KEY_DOWN(KEY_TYPE::UP))
	{
		m_iRestartColor = 200;
		m_iExitColor = 0;
		m_iMyIdxNum = 0;
	}
	else if (KEY_DOWN(KEY_TYPE::S) || KEY_DOWN(KEY_TYPE::DOWN))
	{
		m_iRestartColor = 0;
		m_iExitColor = 200;
		m_iMyIdxNum = 1;
	}*/

	if (KEY_DOWN(KEY_TYPE::SPACE))
	{
		EventMgr::GetInst()->SceneChange(L"StageSelect_Scene");
		/*switch (m_iMyIdxNum)
		{
		case 0:
			break;
		case 1:
			exit(1);
		default:
			break;
		}*/
	}
}

void PlayerDieScene::Render(HDC _dc)
{
	HWND hWnd = Core::GetInst()->GetHwnd();
	ReStart(_dc, hWnd);
}

void PlayerDieScene::ReStart(HDC _dc, HWND hWnd)
{
	//Restart
	SetTextColor(_dc, RGB(255, 0, 255));

	HFONT hFont = CreateFont(m_iFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, L"Arial");
	SelectObject(_dc, hFont);
	RECT restartRect;
	GetClientRect(hWnd, &restartRect);
	DrawText(_dc, L"space바 입력 시 재시작", -1, &restartRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}