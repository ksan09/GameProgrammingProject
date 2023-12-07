#include "pch.h"
#include "PlayerDirCollider.h"
#include "Rigidbody2D.h"
#include "Collider.h"
#include "Object.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "EventMgr.h"
#include "HitEffect.h"
#include "Core.h"
#include "ResMgr.h"

PlayerDirCollider::PlayerDirCollider()
	: m_pOwner(nullptr)
	, m_eState(DIR::TOP)
{
	CreateCollider();
	SetName(L"DIRCOL");
}

PlayerDirCollider::~PlayerDirCollider()
{
}

void PlayerDirCollider::Update()
{
	if (m_pOwner == nullptr)
		return;

	SetPos(m_pOwner->GetPos()); // 플레이어 위치로 이동
}

void PlayerDirCollider::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	wstring objName = pOtherObj->GetName();
	// Block
	if (objName == L"Block" || objName == L"Ground" || objName == L"FallingBlock")
		BlockCheck();

	// DamageAndJumpAbleObject
	if (objName == L"DamageAndJumpAbleObject")
	{
		JumpAbleObjectCheck();
	}
	if (m_eState == DIR::BOTTOM && objName == L"DamageObject")
	{
		m_pOwner->Die();
	}
	
}

void PlayerDirCollider::ExitCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();

	wstring objName = pOtherObj->GetName();
	// Block
	if (objName == L"Block" || objName == L"Ground" || objName == L"FallingBlock")
		BlockCheckOut();

	// DamageAndJumpAbleObject
}

void PlayerDirCollider::SetCollider(DIR state, Vec2 scale, Vec2 offset)
{
	Collider* col = GetCollider();
	col->SetScale(scale);
	col->SetOffSetPos(offset);

	m_eState = state;

	if (m_eState == DIR::BOTTOM)
		SetName(L"DIR_BOTTOM_COL");
}

void PlayerDirCollider::BlockCheck()
{
	Rigidbody2D* rb = m_pOwner->GetRigidbody2D();
	Vec2 velo = rb->GetVelocity();

	switch (m_eState)
	{
	case DIR::LEFT: // 조건 체크 후 스탑 x
		rb->StopMoveLeft(true); // 스탑 레프트 무브
		break;
	case DIR::TOP: // 스탑 Y
		if (velo.y < 0)
			rb->StopVeloY();
		break;
	case DIR::RIGHT: // 조건 체크 후 스탑 x
		rb->StopMoveRight(true); // 스탑 라이트 무브
		break;
	case DIR::BOTTOM: // 스탑 Y하고 그라운드 체킹해주기
		if (velo.y > 0)
		{
			//그라운드 체킹
			
			m_pOwner->SetIsJump(false);
			m_pOwner->SetIsDoubleJump(false);
			rb->StopVeloY();
			rb->SetUseGravity(false);
		}
		
		break;
	default:
		break;
	}
}

void PlayerDirCollider::JumpAbleObjectCheck()
{
	if (m_pOwner->GetDie())
		return;

	switch (m_eState)
	{
	case DIR::BOTTOM: // 점프 및 더블 점프 초기화
		{
			m_pOwner->SetIsJump(false);
			m_pOwner->SetIsDoubleJump(false);
			m_pOwner->Jump();
			Core::GetInst()->Shake(0.2f, 0.5f);

			ResMgr::GetInst()->Play(L"StepJump");

			Vec2 pos = GetPos();
			pos.y += 25;

			HitEffect* pHitEffect = new HitEffect;
			pHitEffect->SetPos(pos);
			SceneMgr::GetInst()->GetCurScene()->AddObject(pHitEffect, OBJECT_GROUP::EFFECT);
		}
		break;
	default:
		break;
	}
}

void PlayerDirCollider::BlockCheckOut()
{
	Rigidbody2D* rb = m_pOwner->GetRigidbody2D();
	Vec2 velo = rb->GetVelocity();

	if (m_eState == DIR::BOTTOM)
	{
		m_pOwner->SetIsJump(true);
		rb->SetUseGravity(true);
	}

	if (m_eState == DIR::LEFT || m_eState == DIR::RIGHT)
	{
		rb->StopMoveLeft(false);
		rb->StopMoveRight(false);
	}
	

}
