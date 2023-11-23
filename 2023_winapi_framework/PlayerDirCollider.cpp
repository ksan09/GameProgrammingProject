#include "pch.h"
#include "PlayerDirCollider.h"
#include "Collider.h"

PlayerDirCollider::PlayerDirCollider()
	: m_pOwner(nullptr)
	, m_eState(DIR::TOP)
{
	CreateCollider();
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
	if (objName == L"Block")
		BlockCheck();
	// DamageObject
	if (objName == L"DamageObject")
		DamageObjectCheck();
	// DamageAndJumpAbleObject
	if (objName == L"DamageAndJumpAbleObject")
		DamageAndJumpAbleObjectCheck();
	
}

void PlayerDirCollider::SetCollider(DIR state, Vec2 scale, Vec2 offset)
{
	Collider* col = GetCollider();
	col->SetScale(scale);
	col->SetOffSetPos(offset);

	m_eState = state;
}

void PlayerDirCollider::BlockCheck()
{
	switch (m_eState)
	{
	case DIR::LEFT: // 조건 체크 후 스탑 x
		break;
	case DIR::TOP: // 스탑 Y
		break;
	case DIR::RIGHT: // 조건 체크 후 스탑 x
		break;
	case DIR::BOTTOM: // 스탑 Y하고 그라운드 체킹해주기
		break;
	default:
		break;
	}
}

void PlayerDirCollider::DamageObjectCheck()
{
	// 사망
}

void PlayerDirCollider::DamageAndJumpAbleObjectCheck()
{
	switch (m_eState)
	{
	case DIR::BOTTOM: // 점프 및 더블 점프 초기화
		break;
	default:
		break;
	}
}
