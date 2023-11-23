#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Rigidbody2D.h"


Player::Player()
	: m_pTex(nullptr)
{
	//m_pTex = new Texture;
	//wstring strFilePath = PathMgr::GetInst()->GetResPath();
	//strFilePath += L"Texture\\plane.bmp";
	//m_pTex->Load(strFilePath);
	//m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\plane.bmp");
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\player.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,30.f));
	//GetCollider()->SetOffSetPos(Vec2(50.f,0.f));
	
	CreateAnimator();
	GetAnimator()->CreateAnim(L"Player_Left", m_pTex, Vec2(0.f, 32.f),
		Vec2(32.f, 32.f), Vec2(32.f, 0.f), 6, 0.2f);
	GetAnimator()->CreateAnim(L"Player_Right", m_pTex, Vec2(192.f, 32.f),
		Vec2(32.f, 32.f), Vec2(32.f, 0.f), 6, 0.2f);
	GetAnimator()->PlayAnim(L"Player_Left", true);

	CreateRigidbody2D();
	//// ������ �ǵ帮��
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	//// �ϳ���
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// ������ �� 
	//for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	//	pAnim->SetFrameOffset(i, Vec2(0.f, 20.f));
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	Rigidbody2D* pRb = GetRigidbody2D();
	Vec2 vVelo = pRb->GetVelocity();

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		pRb->SetVelocity({ -200.f, vVelo.y });
		GetAnimator()->PlayAnim(L"Player_Left", true);
	}
	else if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		pRb->SetVelocity({ 200.f, vVelo.y });
		GetAnimator()->PlayAnim(L"Player_Right", true);
	}
	else
	{
		pRb->SetVelocity({ 0.f, vVelo.y });
	}

	if (KEY_DOWN(KEY_TYPE::SPACE))
	{
		ResMgr::GetInst()->Play(L"Shoot");
		Jump();
	}

	GetAnimator()->Update();
	GetRigidbody2D()->LateUpdate();
}

// ���־�� �� ��
// �ٴڿ� ������ ���߱�
// ���鿡 ������ ���߱�
// ������ �Ϳ� �������� ������ �ױ�
// �������� ������ ��������
// ���������� ������Ʈ�� ������ �����ϱ�
// 

void Player::EnterCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Ground")
	{
		Rigidbody2D* pRigidbody2D = GetRigidbody2D();
		pRigidbody2D->StopVeloY();
	}

}

void Player::Jump()
{
	Rigidbody2D* pRb = GetRigidbody2D();
	Vec2 vVelo = pRb->GetVelocity();

	pRb->SetVelocity({vVelo.x, -500.f});
}

void Player::Render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();
	//int Width = m_pTex->GetWidth();
	//int Height = m_pTex->GetHeight();
	//// 1. �⺻ �ű��
	//BitBlt(_dc
	//	,(int)(vPos.x - vScale.x /2)
	//	,(int)(vPos.y - vScale.y /2)
	//	, Width,Height, m_pTex->GetDC()
	//	,0,0,SRCCOPY);

	//// 2. ���� �Ⱦ��
	//TransparentBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width,Height, RGB(255,0,255));

	//// 3. Ȯ�� �� ���
	//StretchBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width ,Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, SRCCOPY);

	// 4. ȸ��
	// �ﰢ�Լ�, ȸ�����
	//Plgblt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, RGB(255, 0, 255));
	Component_Render(_dc);
}
