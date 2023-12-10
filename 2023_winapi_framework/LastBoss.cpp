#include "pch.h"
#include "LastBoss.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Node.h"
#include "Boss3Node.h"
#include "BehaviorTree.h"
#include "LastBossNode.h"
#include "Collider.h"

#include "DefaultMonster.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "Core.h"

LastBoss::LastBoss(Object* target)
	: m_iHp(4)
	, m_pTarget(target)
	, m_iCurTime(0)
	, m_iDamageDelayTime(1.5f)
	, m_isDamage(false)
	, m_isSpawn(false)
	, m_fSpawnTime(1.0f)
	, m_isDie(false)
{
#pragma region Collider
	CreateCollider();
	GetCollider()->SetScale({ 32.f, 64.f });
	GetCollider()->SetOffSetPos({ 0.f, 12.f });
	SetName(L"DamageAndJumpAbleObject");
#pragma endregion

#pragma region Animator
	float sizeX = 192.f, sizeY = 160.f;

	m_pTex = ResMgr::GetInst()->TexLoad(L"LastBoss", L"Texture\\LastBoss.bmp");

	CreateAnimator();
	//
	GetAnimator()->CreateAnim(L"LB_Appear", m_pTex, Vec2(0.f, 0.f),
		Vec2(sizeX, sizeY), Vec2(sizeX, 0.f), 15, 0.1f);
	GetAnimator()->CreateAnim(L"LB_Idle", m_pTex, Vec2(0.f, sizeY),
		Vec2(sizeX, sizeY), Vec2(sizeX, 0.f), 4, 0.1f);
	GetAnimator()->CreateAnim(L"LB_Move", m_pTex, Vec2(0.f, sizeY * 2),
		Vec2(sizeX, sizeY), Vec2(sizeX, 0.f), 6, 0.05f);
	GetAnimator()->CreateAnim(L"LB_Skill", m_pTex, Vec2(0.f, sizeY * 3),
		Vec2(sizeX, sizeY), Vec2(sizeX, 0.f), 10, 0.1f);
	GetAnimator()->CreateAnim(L"LB_Damage", m_pTex, Vec2(0.f, sizeY * 4),
		Vec2(sizeX, sizeY), Vec2(sizeX, 0.f), 3, 0.1f);
	//
	GetAnimator()->PlayAnim(L"LB_Appear", false);
#pragma endregion

#pragma region AI
	RandomPatternNode* randPatternNode = new RandomPatternNode();

#pragma region pattern1Node
	SequenceNode* patternSeqNode = new SequenceNode();
	LastBossPatternNode1* pattern1Node = new LastBossPatternNode1(this, m_pTarget);

	patternSeqNode->RegisterChild(pattern1Node);
	patternSeqNode->RegisterChild(pattern1Node);

	randPatternNode->RegisterChild(patternSeqNode);
#pragma endregion

#pragma region pattern2Node
	LastBossPatternNode2* pattern2Node = new LastBossPatternNode2(this, m_pTarget);

	randPatternNode->RegisterChild(pattern2Node);
#pragma endregion

#pragma region pattern3Node
	LastBossPatternNode3* pattern3Node = new LastBossPatternNode3(this, m_pTarget);

	randPatternNode->RegisterChild(pattern3Node);
#pragma endregion


#pragma endregion
	//
	//여기에 AI짜서 넣어야 함
	//RepeatNode* rootNode = new RepeatNode(pattern3Node);
	RepeatNode* rootNode = new RepeatNode(randPatternNode);
	m_pTree = new BehaviorTree(rootNode);
}

LastBoss::~LastBoss()
{
	if (m_pTree != nullptr)
		delete m_pTree;
}

void LastBoss::Update()
{
	if(m_isSpawn)
		GetAnimator()->Update();
	else
	{
		m_iCurTime += fDT;
		if (m_iCurTime >= m_fSpawnTime)
		{
			GetAnimator()->Update();
			if (m_iCurTime >= 0.3f)
			{
				ResMgr::GetInst()->Play(L"SpikeUp");
				Core::GetInst()->Shake(0.1f, 1);
				m_fSpawnTime -= m_iCurTime;
				m_iCurTime = 0;
			}

			if (m_fSpawnTime <= -1.f)
			{
				m_isSpawn = true;
				GetAnimator()->PlayAnim(L"LB_Idle", true);
				
			}
		}
		return;
	}

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

			NODE_STATE state = m_pTree->Update();

			GetAnimator()->PlayAnim(L"LB_Move", true);
		}
	}
	else
	{
		NODE_STATE state = m_pTree->Update();
	}
}

void LastBoss::EnterCollision(Collider* _pOther)
{
	if (m_isDamage) return;

	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"DIR_BOTTOM_COL")
	{
		--m_iHp;
		SetName(L"None");
		m_isDamage = true;
		m_iCurTime = 0;

		GetAnimator()->PlayAnim(L"LB_Damage", true);
	}
}

void LastBoss::Render(HDC _dc)
{
	Component_Render(_dc);
}

void LastBoss::Die()
{
	if (m_isDie) return;

	m_isDie = true;
	EventMgr::GetInst()->SceneChange(L"Ending_Scene");
}
