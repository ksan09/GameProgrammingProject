#include "pch.h"
#include "Boss3.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Node.h"
#include "Boss3Node.h"
#include "Collider.h"

#include "DefaultMonster.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "SaveLoadMgr.h"

Boss3::Boss3(Object* target)
	: m_iHp(3)
	, m_pTarget(target)
	, m_iCurTime(0)
	, m_iDamageDelayTime(1.5f)
	, m_isDamage(false)
{
	float size = 96.f;

#pragma region Collider
	CreateCollider();
	GetCollider()->SetScale({ 32.f, 64.f });
	GetCollider()->SetOffSetPos({ 0.f, -4.f });
	SetName(L"DamageAndJumpAbleObject");
#pragma endregion
	
#pragma region Animator
	m_pTex = ResMgr::GetInst()->TexLoad(L"Boss3", L"Texture\\Boss3.bmp");

	CreateAnimator();
	//
	GetAnimator()->CreateAnim(L"Boss3_Idle", m_pTex, Vec2(0.f, 0.f),
		Vec2(size, size), Vec2(size, 0.f), 4, 0.2f);
	GetAnimator()->CreateAnim(L"Boss3_Damage", m_pTex, Vec2(0.f, size),
		Vec2(size, size), Vec2(size, 0.f), 3, 0.1f);
		GetAnimator()->PlayAnim(L"Boss3_Idle", true);
#pragma endregion

	// Node 구조 짜기
#pragma region AI_Tree
	RandomPatternNode* randPatternNode = new RandomPatternNode();

#pragma region pattern1
	// 이동 노드
	SequenceNode* pattern1SeqNode = new SequenceNode();

	RandomPatternNode* randMoveNode = new RandomPatternNode();
	MoveNode* moveRightNode = new MoveNode(this, Vec2(WINDOW_WIDTH - 64, 160), 500);
	MoveNode* moveLeftNode = new MoveNode(this, Vec2(64, 160), 500);

	randMoveNode->RegisterChild(moveLeftNode);
	randMoveNode->RegisterChild(moveRightNode);

	// 공격 노드
	BoundMonsterSpawnPattern1Node* pattern1 = new BoundMonsterSpawnPattern1Node(this, m_pTarget);

	pattern1SeqNode->RegisterChild(randMoveNode);
	pattern1SeqNode->RegisterChild(pattern1);

	randPatternNode->RegisterChild(pattern1SeqNode);
#pragma endregion

#pragma region pattern2
	// Seq
	SequenceNode* pattern2SeqNode = new SequenceNode();
	// MoveNode
	MoveNode* moveUpNode = new MoveNode(this, Vec2(WINDOW_WIDTH / 2, 64), 300);
	// Boss3Pattern2Node
	Boss3Pattern2Node* pattern2Node = new Boss3Pattern2Node(this, m_pTarget);

	pattern2SeqNode->RegisterChild(moveUpNode);
	pattern2SeqNode->RegisterChild(pattern2Node);

	randPatternNode->RegisterChild(pattern2SeqNode);
#pragma endregion

#pragma region pattern3
	SequenceNode* pattern3SeqNode = new SequenceNode();

	Boss3Pattern3Node* pattern3Node = new Boss3Pattern3Node(this, m_pTarget);

	pattern3SeqNode->RegisterChild(randMoveNode);
	pattern3SeqNode->RegisterChild(pattern3Node);
	
	randPatternNode->RegisterChild(pattern3SeqNode);
#pragma endregion


	RepeatNode* rootNode = new RepeatNode(randPatternNode);
	m_pTree = new BehaviorTree(rootNode);
#pragma endregion

	
}

Boss3::~Boss3()
{
	if (m_pTree != nullptr)
		delete m_pTree;
}

void Boss3::Update()
{
	GetAnimator()->Update();

	if (m_isDamage)
	{
		m_iCurTime += fDT;
		if (m_iCurTime >= m_iDamageDelayTime)
		{
			if (m_iHp <= 0)
			{
				Die();
			}

			m_isDamage = false;
			SetName(L"DamageAndJumpAbleObject");
			GetAnimator()->PlayAnim(L"Boss3_Idle", true);
		}
	}
	else
	{
		NODE_STATE state = m_pTree->Update();
	}
	
}

void Boss3::EnterCollision(Collider* _pOther)
{
	if (m_isDamage) return;

	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"DIR_BOTTOM_COL")
	{
		--m_iHp;
		SetName(L"None");
		m_isDamage = true;
		m_iCurTime = 0;

		GetAnimator()->PlayAnim(L"Boss3_Damage", true);
	}
}

void Boss3::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Boss3::Die()
{
	EventMgr::GetInst()->SceneChange(L"StageSelect_Scene");
	EventMgr::GetInst()->DeleteObject(this);
	SaveLoadMgr::GetInst()->Stage3();
}
