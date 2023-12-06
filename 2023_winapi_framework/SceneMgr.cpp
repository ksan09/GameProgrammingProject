#include "pch.h"
#include "SceneMgr.h"
#include "Start_Scene.h"
#include "StageSelectScene.h"
#include "Boss1Scene.h"
#include "Boss2Scene.h"
#include "Boss3Scene.h"
#include "LastBossScene.h"
#include "EndingScene.h"
#include "playerDieScene.h"

void SceneMgr::Init()
{
	m_pCurScene = nullptr;
	// �� ���
	RegisterScene(L"Start_Scene",std::make_shared<Start_Scene>());
	RegisterScene(L"StageSelect_Scene",std::make_shared<StageSelectScene>());
	RegisterScene(L"Boss1_Scene", std::make_shared<Boss1Scene>());
	RegisterScene(L"Boss2_Scene", std::make_shared<Boss2Scene>());
	RegisterScene(L"Boss3_Scene", std::make_shared<Boss3Scene>());
	RegisterScene(L"LastBoss_Scene", std::make_shared<LastBossScene>());
	RegisterScene(L"Ending_Scene", std::make_shared<EndingScene>());
	RegisterScene(L"PlayerDie_Scene", std::make_shared<PlayerDieScene>());

	// ù �� ����
	LoadScene(L"Start_Scene");
}

void SceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->FinalUpdate();
}

void SceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}

void SceneMgr::LoadScene(const wstring& _scenename)
{
	// ���� ������
	if (m_pCurScene != nullptr)
	{
		m_pCurScene->Release(); // ������� ������
		m_pCurScene = nullptr;
	}

	auto iter = m_mapScenes.find(_scenename);
	if (iter != m_mapScenes.end())
	{
		m_pCurScene = iter->second;
		m_pCurScene->Init();
	}
}

void SceneMgr::RegisterScene(const wstring& _scenename, std::shared_ptr<Scene> _scene)
{
	m_mapScenes.insert(m_mapScenes.end(), {_scenename, _scene});
}
