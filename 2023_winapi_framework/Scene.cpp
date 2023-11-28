#include "pch.h"
#include "Scene.h"
#include "Object.h"
Scene::Scene()
{
}

Scene::~Scene()
{
	Release();
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			if(!m_vecObj[i][j]->GetIsDead())
				m_vecObj[i][j]->Update();
		}
	}
}

void Scene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			m_vecObj[i][j]->FinalUpdate();
		}
	}
}

void Scene::Render(HDC _dc)
{
	// ¹è°æ
	HBRUSH hBackBrush = CreateSolidBrush(RGB(212, 217, 216));
	HBRUSH hDefaultBrush = (HBRUSH)SelectObject(_dc, hBackBrush);
	Rectangle(_dc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(_dc, hDefaultBrush);
	DeleteObject(hBackBrush);

	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size();)
		{
			if (!m_vecObj[i][j]->GetIsDead())
			{
				m_vecObj[i][j]->Render(_dc);
				++j;
			}
			else
				m_vecObj[i].erase(m_vecObj[i].begin() + j);
		}
	}
}

void Scene::Release()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			delete m_vecObj[i][j];
		}
		m_vecObj[i].clear();
	}
}
