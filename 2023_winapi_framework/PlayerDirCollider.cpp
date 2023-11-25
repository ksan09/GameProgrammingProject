#include "pch.h"
#include "PlayerDirCollider.h"
#include "Rigidbody2D.h"
#include "Collider.h"
#include "Object.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "EventMgr.h"

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

	SetPos(m_pOwner->GetPos()); // �÷��̾� ��ġ�� �̵�
}

void PlayerDirCollider::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	wstring objName = pOtherObj->GetName();
	// Block
	if (objName == L"Block" || objName == L"Ground")
		BlockCheck();
	// DamageObject
	if (objName == L"DamageObject")
		DamageObjectCheck();
	// DamageAndJumpAbleObject
	if (objName == L"DamageAndJumpAbleObject")
	{
		DamageAndJumpAbleObjectCheck();
	}
	
}

void PlayerDirCollider::ExitCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();

	wstring objName = pOtherObj->GetName();
	// Block
	if (objName == L"Block" || objName == L"Ground")
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
	case DIR::LEFT: // ���� üũ �� ��ž x
		rb->StopMoveLeft(true); // ��ž ����Ʈ ����
		break;
	case DIR::TOP: // ��ž Y
		if (velo.y < 0)
			rb->StopVeloY();
		break;
	case DIR::RIGHT: // ���� üũ �� ��ž x
		rb->StopMoveRight(true); // ��ž ����Ʈ ����
		break;
	case DIR::BOTTOM: // ��ž Y�ϰ� �׶��� üŷ���ֱ�
		if (velo.y > 0)
		{
			//�׶��� üŷ
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

void PlayerDirCollider::DamageObjectCheck()
{
	// ���
	m_pOwner->Die();
}

void PlayerDirCollider::DamageAndJumpAbleObjectCheck()
{
	switch (m_eState)
	{
	case DIR::BOTTOM: // ���� �� ���� ���� �ʱ�ȭ
		m_pOwner->SetIsJump(false);
		m_pOwner->SetIsDoubleJump(false);
		m_pOwner->Jump();
		break;
	default:
		m_pOwner->Die();
		break;
	}
}

void PlayerDirCollider::BlockCheckOut()
{
	Rigidbody2D* rb = m_pOwner->GetRigidbody2D();
	Vec2 velo = rb->GetVelocity();

	if (m_eState == DIR::BOTTOM)
	{
		rb->SetUseGravity(true);
	}

	if (m_eState == DIR::LEFT || m_eState == DIR::RIGHT)
	{
		rb->StopMoveLeft(false);
		rb->StopMoveRight(false);
	}
	

}
