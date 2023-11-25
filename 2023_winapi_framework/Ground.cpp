#include "pch.h"
#include "Ground.h"
#include "ResMgr.h"
#include "Texture.h"

Ground::Ground()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Ground", L"Texture\\Ground.bmp");
	SetName(L"Ground");
}

Ground::~Ground()
{
}
