#include "pch.h"
#include "JumpableBlock.h"
#include "Collider.h"
#include "EventMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Rigidbody2D.h"

JumpableBlock::JumpableBlock()
	: m_isDie(false)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"JumpableBlock", L"Texture\\JumpableBlock.bmp");
	SetName(L"DamageAndJumpAbleObject");

	CreateRigidbody2D();
}

JumpableBlock::~JumpableBlock()
{
}

void JumpableBlock::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	wstring objName = pOtherObj->GetName();
	// Block
	if (objName == L"DamageAndJumpAbleObject")
	{
		return;
	}

	if (objName == L"Block")
	{
		GetRigidbody2D()->StopVeloX();
	}
	else if (objName == L"Ground")
	{
		GetRigidbody2D()->StopVeloX();
		GetRigidbody2D()->StopVeloY();
		GetRigidbody2D()->SetUseGravity(false);
	}
	else if (m_isDie == false)
	{
		m_isDie = true;
		EventMgr::GetInst()->DeleteObject(this);
	}
	
}

void JumpableBlock::Update()
{
	GetRigidbody2D()->LateUpdate();
}
