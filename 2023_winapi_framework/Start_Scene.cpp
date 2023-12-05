#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Block.h"
#include "DefaultMonster.h"
#include "Ground.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ResMgr.h"
#include "Rigidbody2D.h"
#include "Boss3.h"
#include "Spike.h"
#include "Title.h"
#include "EventMgr.h"
#include "GameRule.h"
#include <time.h>

Title* TitleScene;
GameRule* PopUp;

void Start_Scene::Init()
{
	Title* title = new Title;
	title->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	title->SetScale(Vec2(960.f, 640.f));
	AddObject(title, OBJECT_GROUP::DEFAULT);
	TitleScene = title;

	GameRule* gameRule = new GameRule;
	gameRule->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	gameRule->SetScale(Vec2(800.f, 480.f));
	AddObject(gameRule, OBJECT_GROUP::OBJ);
	PopUp = gameRule;

	//// 사운드 세팅
	//ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	//ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	//ResMgr::GetInst()->Play(L"BGM"); 
}

void Start_Scene::Update()
{
	Scene::Update();

	if (!onGameRule && KEY_DOWN(KEY_TYPE::SPACE) || KEY_DOWN(KEY_TYPE::ENTER))
	{
		switch (TitleScene->curIndex)
		{
		case 0:
			EventMgr::GetInst()->SceneChange(L"StageSelect_Scene");
			break;
		case 1:
			onGameRule = true;
			break;
		case 2:
			exit(1);
			break;
		default:
			break;
		}
	}

	if (onGameRule && KEY_DOWN(KEY_TYPE::ESC))
		onGameRule = false;

	if (onGameRule)
	{
		TitleScene->onGameRule = true;
		PopUp->RulePopUp = true;
	}
	else
	{
		TitleScene->onGameRule = false;
		PopUp->RulePopUp = false;
	}
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
