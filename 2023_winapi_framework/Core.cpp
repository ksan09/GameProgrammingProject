#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"
bool Core::Init(HWND _hWnd, POINT _ptResolution)
{
	// === 변수 초기화 === 
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	m_hbackDC = 0;
	m_hbackbit = 0;

	m_fCurTime = 0;
	m_vShakePos = { 0, 0 };
	m_fShakeTime = 0;
	m_fShakePower = 0;
	m_isShake = false;

	// 더블버퍼링
	m_hDC = GetDC(m_hWnd);	
	// 1. 생성
	m_hbackbit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hbackDC = CreateCompatibleDC(m_hDC);

	// 2. 연결
	SelectObject(m_hbackDC, m_hbackbit);

//	m_obj.SetPos(Vec2({ m_ptResolution.x / 2, m_ptResolution.y / 2 }));
////	m_obj.m_ptPos = ;
//	m_obj.SetScale(Vec2(150, 150));

	CreateGDI();
	// ==== Manager Init ====
	PathMgr::GetInst()->Init();
	TimeMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();
	ResMgr::GetInst()->Init();
	SceneMgr::GetInst()->Init();

	return true;
}

void Core::GameLoop()
{
	Update();
	Render();
}


void Core::Shake(float time, float power)
{
	m_isShake = true;
	m_fShakeTime = time;
	m_fShakePower = power;
}

void Core::Update()
{

	// === Manager Update === 
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();
	SceneMgr::GetInst()->Update();
	CollisionMgr::GetInst()->Update();

	//
	if (m_isShake)
	{
		m_fCurTime += fDT;
		if (m_fCurTime >= 0.05f)
		{
			m_vShakePos = { rand() % 21 - 10, rand() % 21 - 10 };	// -10 ~ 10 0 ~ 20
			m_fShakeTime -= m_fCurTime;
			m_fCurTime = 0;
		}

		if (m_fShakeTime <= 0)
			m_isShake = false;
	}
}

void Core::Render()
{
	// 칠한다.
	PatBlt(m_hbackDC, 0, 0, m_ptResolution.x, m_ptResolution.y, WHITENESS);
	SceneMgr::GetInst()->Render(m_hbackDC);

	// 3. 옮긴다.
	// 카메라 쉐이킹?
	if (m_isShake)
	{
		BitBlt(m_hDC, 
			m_vShakePos.x * m_fShakePower, 
			m_vShakePos.y * m_fShakePower,
			m_vShakePos.x * m_fShakePower + m_ptResolution.x,
			m_vShakePos.y * m_fShakePower + m_ptResolution.y,
			m_hbackDC, 0, 0, SRCCOPY);
	}
	else
	{
		BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
			m_hbackDC, 0, 0, SRCCOPY);
	}
	
	EventMgr::GetInst()->Update();
}

void Core::CreateGDI()
{
	// HOLLOW
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	m_arrBrush[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	m_arrBrush[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));

	//RED GREEN BLUE PEN
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
}

void Core::Release()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_hbackDC); // createdc 한거 지우는거
	DeleteObject(m_hbackbit); // createbit 한거 지우는거
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		DeleteObject(m_arrBrush[i]);
	}

	ResMgr::GetInst()->Release();
}
