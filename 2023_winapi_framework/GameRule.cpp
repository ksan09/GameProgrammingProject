#include "pch.h"
#include "GameRule.h"
#include "Texture.h"
#include "ResMgr.h"
#include "Animator.h"
#include "KeyMgr.h"

GameRule::GameRule()
	: m_pTex(nullptr)
	, RulePopUp(false)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"GameRule", L"Texture\\GAMERULE.bmp");
}

GameRule::~GameRule()
{
}

void GameRule::Update()
{

}

void GameRule::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();

	if (RulePopUp)
		BitBlt(_dc
			, (int)(vPos.x - vScale.x / 2)
			, (int)(vPos.y - vScale.y / 2)
			, Width, Height, m_pTex->GetDC()
			, 0, 0, SRCCOPY);
	//Component_Render(_dc);
}
