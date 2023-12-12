#include "pch.h"
#include "Boss1.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Node.h"
#include "Collider.h"
#include "Rigidbody2D.h"

#include "DefaultMonster.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "Boss1Node.h"
#include "SaveLoadMgr.h"

Boss1::Boss1(Object* target)
	: m_iHp(4)
	, m_pTarget(target)
	, m_iCurTime(0)
	, m_fDieTime(0)
	, m_iDelayTime(1.5f)
	, m_isDamage(false)
	, m_isGround(false)
	, m_isDie(false)
{
	CreateRigidbody2D();

#pragma region Collider
	CreateCollider();
	GetCollider()->SetScale({ 32.f, 38.f });
	GetCollider()->SetOffSetPos({ 0.f, -18.f });
	SetName(L"DamageAndJumpAbleObject");
#pragma endregion

#pragma region Animator
	float sizeX = 160.f, sizeY = 128.f;

	m_pTex = ResMgr::GetInst()->TexLoad(L"Boss1", L"Texture\\Boss1.bmp");

	CreateAnimator();
	//
	GetAnimator()->CreateAnim(L"Boss1_Idle", m_pTex, Vec2(0.f, 0.f),
		Vec2(sizeX, sizeY), Vec2(sizeX, 0.f), 4, 0.1f);
	GetAnimator()->CreateAnim(L"Boss1_JumpUp", m_pTex, Vec2(0.f, sizeY),
		Vec2(sizeX, sizeY), Vec2(sizeX, 0.f), 4, 0.1f);
	GetAnimator()->CreateAnim(L"Boss1_FallDown", m_pTex, Vec2(sizeX * 3, sizeY),
		Vec2(sizeX, sizeY), Vec2(-sizeX, 0.f), 4, 0.1f);
	GetAnimator()->CreateAnim(L"Boss1_Damage", m_pTex, Vec2(0.f, sizeY * 2),
		Vec2(sizeX, sizeY), Vec2(sizeX, 0.f), 3, 0.1f);
	//
	GetAnimator()->PlayAnim(L"Boss1_Idle", true);
#pragma endregion


	SequenceNode* pattern1SeqNode = new SequenceNode();
	RandomPatternNode1* randPatternNode = new RandomPatternNode1();

#pragma region 점프 노드

	JumpNode* jumpNode = new JumpNode(this, m_pTarget, 500);
#pragma endregion

	// 공격 노드
	BoundMonsterSpawnPattern1Node1* pattern1 = new BoundMonsterSpawnPattern1Node1(this, m_pTarget);
	Boss1Pattern2Node* pattern2 = new Boss1Pattern2Node(this, m_pTarget);

	pattern1SeqNode->RegisterChild(pattern1);
	pattern1SeqNode->RegisterChild(jumpNode);
	pattern1SeqNode->RegisterChild(pattern2);

	randPatternNode->RegisterChild(pattern1SeqNode);

	//여기에 AI짜서 넣어야 함
	RepeatNode* rootNode = new RepeatNode(randPatternNode);
	m_pTree = new BehaviorTree(rootNode);
}

Boss1::~Boss1()
{
	if (m_pTree != nullptr)
		delete m_pTree;
}

void Boss1::Update()
{
	GetAnimator()->Update();

	//죽을 때 씬 넘기기 안됨
	if (m_isDie)
	{
		m_fDieTime += fDT;
		if (m_fDieTime >= 2.f)
			EventMgr::GetInst()->SceneChange(L"StageSelect_Scene");
	}

	if (m_isDamage)
	{
		m_iCurTime += fDT;
		if (m_iCurTime >= m_iDelayTime)
		{
			if (m_iHp <= 0)
			{
				Die();
			}
			m_isDamage = false;
			SetName(L"DamageAndJumpAbleObject");
			GetAnimator()->PlayAnim(L"Boss1_Idle", true);
		}
	}
	else
	{
		NODE_STATE state = m_pTree->Update();
	}

	GetRigidbody2D()->LateUpdate();
}

void Boss1::ExitCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Ground")
	{
		m_isGround = false;
		GetRigidbody2D()->SetUseGravity(true);
		GetAnimator()->PlayAnim(L"Boss1_JumpUp", false);
	}
}

void Boss1::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Ground")
	{
		if (!m_isGround)
			GetAnimator()->PlayAnim(L"Boss1_FallDown", false);

		m_isGround = true;

		GetAnimator()->PlayAnim(L"Boss1_Idle", true);

		GetRigidbody2D()->Stop();
		GetRigidbody2D()->SetUseGravity(false);
	}

	if (m_isDamage) return;

	if (pOtherObj->GetName() == L"DIR_BOTTOM_COL")
	{
		--m_iHp;
		SetName(L"None");
		m_isDamage = true;
		m_iCurTime = 0;

		GetAnimator()->PlayAnim(L"Boss1_Damage", true);
	}
}

void Boss1::Render(HDC _dc)
{
	Component_Render(_dc);
}

void Boss1::Die()
{
	SaveLoadMgr::GetInst()->Stage1();
	EventMgr::GetInst()->SceneChange(L"StageSelect_Scene");
	m_isDie = true;
}
