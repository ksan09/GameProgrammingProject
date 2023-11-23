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

	SetPos(m_pOwner->GetPos()); // �÷��̾� ��ġ�� �̵�
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
	case DIR::LEFT: // ���� üũ �� ��ž x
		break;
	case DIR::TOP: // ��ž Y
		break;
	case DIR::RIGHT: // ���� üũ �� ��ž x
		break;
	case DIR::BOTTOM: // ��ž Y�ϰ� �׶��� üŷ���ֱ�
		break;
	default:
		break;
	}
}

void PlayerDirCollider::DamageObjectCheck()
{
	// ���
}

void PlayerDirCollider::DamageAndJumpAbleObjectCheck()
{
	switch (m_eState)
	{
	case DIR::BOTTOM: // ���� �� ���� ���� �ʱ�ȭ
		break;
	default:
		break;
	}
}
