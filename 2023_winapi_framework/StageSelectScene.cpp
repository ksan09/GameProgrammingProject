#include "pch.h"
#include "StageSelectScene.h"
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

void StageSelectScene::Init()
{
	Object* pObj = new Player;
	pObj->SetPos((Vec2({ 192, WINDOW_HEIGHT - 128 })));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	Block* pBlock1 = new Ground;
	pBlock1->SetPos((Vec2(WINDOW_WIDTH / 2 - 4, WINDOW_HEIGHT - 32)));
	pBlock1->SetBlock((Vec2(WINDOW_WIDTH, 160)));
	AddObject(pBlock1, OBJECT_GROUP::OBJ);

#pragma region StageSelect
	Gate* pTurotial = new Gate(false);
	pTurotial->SetGateScene(L"Tutorial_Scene");
	pTurotial->SetPos((Vec2(WINDOW_WIDTH / 2 + 4, WINDOW_HEIGHT - 160 + 6)));
	AddObject(pTurotial, OBJECT_GROUP::OBJ);

	TextObject* pText0 = new TextObject(L" Tutorial ");
	pText0->SetPos((Vec2(WINDOW_WIDTH / 2 - 24, WINDOW_HEIGHT - 220)));
	AddObject(pText0, OBJECT_GROUP::OBJ);

	Gate* pGate1 = new Gate(false);
	pGate1->SetGateScene(L"Boss1_Scene");
	pGate1->SetPos((Vec2(192+4, WINDOW_HEIGHT - 352 + 6)));
	AddObject(pGate1, OBJECT_GROUP::OBJ);
	
	TextObject* pText1 = new TextObject(L" Boss 1 ");
	pText1->SetPos((Vec2(192 -22, WINDOW_HEIGHT - 412)));
	AddObject(pText1, OBJECT_GROUP::OBJ);

	Gate* pGate2 = new Gate(false);
	pGate2->SetGateScene(L"Boss2_Scene");
	pGate2->SetPos((Vec2(WINDOW_WIDTH / 2 + 4, WINDOW_HEIGHT - 352 + 6)));
	AddObject(pGate2, OBJECT_GROUP::OBJ);

	TextObject* pText2 = new TextObject(L" Boss 2 ");
	pText2->SetPos((Vec2(WINDOW_WIDTH / 2 - 22, WINDOW_HEIGHT - 412)));
	AddObject(pText2, OBJECT_GROUP::OBJ);
	
	Gate* pGate3 = new Gate(false);
	pGate3->SetGateScene(L"Boss3_Scene");
	pGate3->SetPos((Vec2(WINDOW_WIDTH - 192 + 4, WINDOW_HEIGHT - 352 + 6)));
	AddObject(pGate3, OBJECT_GROUP::OBJ);

	TextObject* pText3 = new TextObject(L" Boss 3 ");
	pText3->SetPos((Vec2(WINDOW_WIDTH - 192 - 22, WINDOW_HEIGHT - 412)));
	AddObject(pText3, OBJECT_GROUP::OBJ);
	
	Block* pBlock4 = new Block;
	pBlock4->SetPos((Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 192 - 96)));
	pBlock4->SetBlock((Vec2(96.f, 32.f)));
	pBlock4->SetSize(3);
	AddObject(pBlock4, OBJECT_GROUP::OBJ);
	
	Gate* pGateEnd = new Gate(true);
	pGateEnd->SetGateScene(L"LastBoss_Scene");
	pGateEnd->SetPos((Vec2(WINDOW_WIDTH / 2 + 4, WINDOW_HEIGHT - 352 - 192 + 6)));
	AddObject(pGateEnd, OBJECT_GROUP::OBJ);

	TextObject* pTextE = new TextObject(L" Last Boss ");
	pTextE->SetPos((Vec2(WINDOW_WIDTH / 2 - 32, WINDOW_HEIGHT - 412 - 192)));
	AddObject(pTextE, OBJECT_GROUP::OBJ);

	Block* pBlock7 = new Block;
	pBlock7->SetPos((Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 192 - 96 - 192)));
	pBlock7->SetBlock((Vec2(96.f, 32.f)));
	pBlock7->SetSize(3);
	AddObject(pBlock7, OBJECT_GROUP::OBJ);
	
	Block* pBlock5 = new Block;
	pBlock5->SetPos((Vec2(192, WINDOW_HEIGHT - 192 - 96)));
	pBlock5->SetBlock((Vec2(96.f, 32.f)));
	pBlock5->SetSize(3);
	AddObject(pBlock5, OBJECT_GROUP::OBJ);
	
	Block* pBlock6 = new Block;
	pBlock6->SetPos((Vec2(WINDOW_WIDTH - 192, WINDOW_HEIGHT - 192 - 96)));
	pBlock6->SetBlock((Vec2(96.f, 32.f)));
	pBlock6->SetSize(3);
	AddObject(pBlock6, OBJECT_GROUP::OBJ);

#pragma endregion


	srand((unsigned int)time(nullptr));
	//

	Vec2 vResolution = Core::GetInst()->GetResolution();

	// 사운드 세팅
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::BGM, 1.f);
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, 0.6f);
	ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResMgr::GetInst()->Play(L"BGM");

	// 충돌체크해야되는것들을 설정하자.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER_DIR_COL, OBJECT_GROUP::OBJ);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::OBJ, OBJECT_GROUP::PLAYER);

	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::OBJ, OBJECT_GROUP::BOTTOM_COL);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::OBJ, OBJECT_GROUP::OBJ);
}

void StageSelectScene::Update()
{
	Scene::Update();
}

void StageSelectScene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void StageSelectScene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
