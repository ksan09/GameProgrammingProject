#include "pch.h"
#include "Boss2Scene.h"
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
#include "Boss2.h"
#include "Spike.h"
#include <time.h>

void Boss2Scene::Init()
{
	Object* pObj = new Player;
	pObj->SetPos((Vec2({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 })));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	Block* pBlock1 = new Ground;
	pBlock1->SetPos((Vec2(WINDOW_WIDTH / 2 - 4, WINDOW_HEIGHT - 32)));
	pBlock1->SetBlock((Vec2(WINDOW_WIDTH, 160)));
	AddObject(pBlock1, OBJECT_GROUP::OBJ);

	Boss2* pBoss = new Boss2(pObj);
	pBoss->SetPos(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 256.f - 12.f));
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

void Boss2Scene::Update()
{
	Scene::Update();
}

void Boss2Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Boss2Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
