#include "pch.h"
#include "TutorialScene.h"
#include "CollisionMgr.h"
#include "Core.h"
#include "Ground.h"
#include "Object.h"
#include "Player.h"
#include <ctime>
#include "ResMgr.h"
#include "KeyMgr.h"
#include "Gate.h"
#include "SceneMgr.h"
#include "TextObject.h"
#include "TimeMgr.h"
#include "DefaultMonster.h"
#include "Bullet.h"

TutorialScene::TutorialScene()
	: m_monsterObj(nullptr)
	, m_fCurTime(0)
{
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Init()
{

	Object* pObj = new Player;
	pObj->SetPos((Vec2({ 192, WINDOW_HEIGHT - 128 })));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	Block* pBlock1 = new Ground;
	pBlock1->SetPos((Vec2(WINDOW_WIDTH / 2 - 4, WINDOW_HEIGHT - 32)));
	pBlock1->SetBlock((Vec2(WINDOW_WIDTH, 160)));
	AddObject(pBlock1, OBJECT_GROUP::OBJ);
	
#pragma region Gate
	Gate* pGate1 = new Gate(false);
	pGate1->SetGateScene(L"StageSelect_Scene");
	pGate1->SetPos((Vec2(WINDOW_WIDTH - 76, 128 + 6)));
	AddObject(pGate1, OBJECT_GROUP::OBJ);

	TextObject* pText1 = new TextObject(L" Back ");
	pText1->SetPos((Vec2(WINDOW_WIDTH - 76 - 20, 128 - 60)));
	AddObject(pText1, OBJECT_GROUP::OBJ);
#pragma endregion
#pragma region Block
	Block* pBlock2 = new Block;
	pBlock2->SetPos((Vec2(196 - 8, WINDOW_HEIGHT - 192 - 96)));
	pBlock2->SetBlock((Vec2(384.f, 32.f)));
	pBlock2->SetSize(12);
	AddObject(pBlock2, OBJECT_GROUP::OBJ);

	Block* pBlock3 = new Block;
	pBlock3->SetPos((Vec2(WINDOW_WIDTH - 80, WINDOW_HEIGHT - 192 - 256)));
	pBlock3->SetBlock((Vec2(160.f, 32.f)));
	pBlock3->SetSize(5);
	AddObject(pBlock3, OBJECT_GROUP::OBJ);
#pragma endregion
#pragma region Text
	TextObject* jumpExplain = new TextObject(L"Press \"space\" to jump");
	jumpExplain->SetPos(Vec2(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT - 200));
	AddObject(jumpExplain, OBJECT_GROUP::EFFECT);

	TextObject* jumpExplain2 = new TextObject(L"You can \"Double Jump\"");
	jumpExplain2->SetPos(Vec2(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT - 280));
	AddObject(jumpExplain2, OBJECT_GROUP::EFFECT);

	TextObject* jumpExplain3 = new TextObject(L"and reset \"Double Jump\"");
	jumpExplain3->SetPos(Vec2(WINDOW_WIDTH / 2 - 112 + 64, WINDOW_HEIGHT - 480));
	AddObject(jumpExplain3, OBJECT_GROUP::EFFECT);

	TextObject* monsterExplain = new TextObject(L"Step on monsters to deal damage,");
	monsterExplain->SetPos(Vec2(WINDOW_WIDTH / 2 - 112 + 64, WINDOW_HEIGHT - 500));
	AddObject(monsterExplain, OBJECT_GROUP::EFFECT);

	TextObject* monsterExplain2 = new TextObject(L"If you touch a monster from the side, you die.");
	monsterExplain2->SetPos(Vec2(WINDOW_WIDTH / 2 - 144 + 64, WINDOW_HEIGHT - 380 ));
	AddObject(monsterExplain2, OBJECT_GROUP::EFFECT);

	TextObject* bulletExplain = new TextObject(L"If you get hit by a bullet, you're dead.");
	bulletExplain->SetPos(Vec2(64, WINDOW_HEIGHT - 380));
	AddObject(bulletExplain, OBJECT_GROUP::EFFECT);

	Bullet* bullet = new Bullet();
	bullet->SetPos(Vec2(96, WINDOW_HEIGHT - 340));
	AddObject(bullet, OBJECT_GROUP::OBJ);
#pragma endregion


	Vec2 vResolution = Core::GetInst()->GetResolution();

	// 사운드 세팅

	// 충돌체크해야되는것들을 설정하자.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER_DIR_COL, OBJECT_GROUP::OBJ);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::OBJ, OBJECT_GROUP::PLAYER);

	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER_DIR_COL, OBJECT_GROUP::BOSS);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::OBJ, OBJECT_GROUP::BOSS);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::BOSS);

	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::OBJ, OBJECT_GROUP::BOTTOM_COL);

	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::OBJ, OBJECT_GROUP::OBJ);
}

void TutorialScene::Update()
{
	if (m_monsterObj != nullptr && m_monsterObj->GetIsDead())
		m_monsterObj = nullptr;

	if (m_monsterObj == nullptr)
	{
		m_fCurTime += fDT;
		if (m_fCurTime > 1.f)
		{
			m_fCurTime = 0;
			m_monsterObj = new DefaultMonster();
			m_monsterObj->SetBlock({ 32.f, 32.f });
			m_monsterObj->GetRigidbody2D()->SetUseGravity(false);
			m_monsterObj->SetPos(Vec2(WINDOW_WIDTH / 2 - 8 + 64, WINDOW_HEIGHT - 420));
			AddObject(m_monsterObj, OBJECT_GROUP::OBJ);
		}
	}

	Scene::Update();
}

void TutorialScene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void TutorialScene::Release()
{
	m_monsterObj = nullptr;
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
