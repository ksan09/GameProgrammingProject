#include "pch.h"
#include "Gate.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "EventMgr.h"

#include "Animator.h"
#include "Collider.h"
#include "Object.h"

Gate::Gate(int v)
	: m_isLoadScene(false)
{
	if(v == 1)
		m_pTex = ResMgr::GetInst()->TexLoad(L"LastBossGate", L"Texture\\LastBossGate.bmp");
	else if (v == 2)
		m_pTex = ResMgr::GetInst()->TexLoad(L"NormalGate", L"Texture\\NormalGate.bmp");
	else
		m_pTex = ResMgr::GetInst()->TexLoad(L"Gate", L"Texture\\Gate.bmp");
	SetName(L"Gate");

	m_sceneName = L"";

	CreateAnimator();
	float size = 96.f;
	if (v <= 1)
	{
		GetAnimator()->CreateAnim(L"GateIdle", m_pTex,
			Vec2(0, 0), Vec2(size, size), Vec2(size, 0.f), 9, 0.05f);	
		GetAnimator()->PlayAnim(L"GateIdle", true);
	}
	else
	{
		GetAnimator()->CreateAnim(L"GateIdle", m_pTex,
			Vec2(0, 0), Vec2(size, size), Vec2(size, 0.f), 1, 0.05f);
		GetAnimator()->PlayAnim(L"GateIdle", false);
	}
	
	CreateCollider();
	GetCollider()->SetOffSetPos({ 0.f, 48.f });
	GetCollider()->SetScale({ 16.f, 8.f });
}

Gate::~Gate()
{
}

void Gate::Update()
{
	GetAnimator()->Update();
}

void Gate::EnterCollision(Collider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"DIR_BOTTOM_COL")
	{
		if (m_sceneName == L"")
			return;
			
		if (m_isLoadScene)
			return;
	
		m_isLoadScene = true;
		ResMgr::GetInst()->Play(L"StageChange");
		EventMgr::GetInst()->SceneChange(m_sceneName);
	}
}

void Gate::Render(HDC _dc)
{
	Component_Render(_dc);
}
