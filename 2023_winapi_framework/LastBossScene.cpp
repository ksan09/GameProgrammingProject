#include "pch.h"
#include "LastBossScene.h"
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
#include "LastBoss.h"
#include "Spike.h"
#include <time.h>

void LastBossScene::Init()
{
	Object* pObj = new Player;
	pObj->SetPos((Vec2({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 })));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	Block* pBlock1 = new Ground;
	pBlock1->SetPos((Vec2(WINDOW_WIDTH / 2 - 4, WINDOW_HEIGHT - 32)));
	pBlock1->SetBlock((Vec2(WINDOW_WIDTH, 160)));
	AddObject(pBlock1, OBJECT_GROUP::OBJ);

	Block* pBlock2 = new Block();
	pBlock2->SetPos((Vec2(WINDOW_WIDTH / 2, 192)));
	pBlock2->SetBlock(Vec2(160.f, 32.f));
	pBlock2->SetSize(5);
	AddObject(pBlock2, OBJECT_GROUP::OBJ);

	LastBoss* pBoss = new LastBoss(pObj);
	pBoss->SetPos(Vec2(WINDOW_WIDTH / 2.f + 4, 96.f + 6.f));
	AddObject(pBoss, OBJECT_GROUP::BOSS);

	srand((unsigned int)time(nullptr));
	//

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

void LastBossScene::Update()
{
	Scene::Update();
}

void LastBossScene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void LastBossScene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
