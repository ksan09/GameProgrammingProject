#include "pch.h"
#include "Block.h"
#include "Collider.h"
#include "Texture.h"
#include "ResMgr.h"

Block::Block()
{
	// Collider
	CreateCollider();
	GetCollider()->SetScale(GetScale());

	m_pTex = ResMgr::GetInst()->TexLoad(L"Block", L"Texture\\Block.bmp");

	SetName(L"Block");

}

Block::~Block()
{
}

void Block::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();

	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2)
		, Width, Height, m_pTex->GetDC()
		, 0, 0, Width, Height, RGB(255, 0, 255));

	Component_Render(_dc);
}

void Block::SetBlock(Vec2 scale)
{
	scale = Vec2(scale.x - 8, scale.y - 8);
	
	SetScale(scale);
	GetCollider()->SetScale(scale);
	GetCollider()->SetOffSetPos(Vec2(4.f, 4.f));
}
