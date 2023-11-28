#include "pch.h"
#include "Boss1.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Animator.h"
#include "Node.h"
#include "Collider.h"

#include "DefaultMonster.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "EventMgr.h"

Boss1::Boss1(Object* target)
	: m_iHp(4)
	, m_pTarget(target)
	, m_iCurTime(0)
	, m_iDamageDelayTime(1)
	, m_isDamage(false)
{

#pragma region Collider
	CreateCollider();
	GetCollider()->SetScale({ 32.f, 32.f });
	GetCollider()->SetOffSetPos({ 0.f, -16.f });
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

	//여기에 AI짜서 넣어야 함
	RepeatNode* rootNode = new RepeatNode(nullptr);
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
			GetAnimator()->PlayAnim(L"Boss1_Idle", true);
		}
	}
	else
	{
		NODE_STATE state = m_pTree->Update();
	}
}

void Boss1::EnterCollision(Collider* _pOther)
{
	if (m_isDamage) return;

	const Object* pOtherObj = _pOther->GetObj();
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
	EventMgr::GetInst()->DeleteObject(this);
}
