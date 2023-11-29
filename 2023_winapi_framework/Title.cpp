#include "pch.h"
#include "Title.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "Animator.h"
//#include "Animation.h"

Title::Title()
	:m_pTex(nullptr)
	, index(0)
	, curIndex(0)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Title", L"Texture\\Title-Sheet.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnim(L"Title_Start", m_pTex, Vec2(0.f, 0.f),
		Vec2(960.f, 640.f), Vec2(960.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Title_GameRule", m_pTex, Vec2(0.f, 640.f),
		Vec2(960.f, 640.f), Vec2(960.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Title_Exit", m_pTex, Vec2(0.f, 1280.f),
		Vec2(960.f, 640.f), Vec2(960.f, 0.f), 5, 0.2f);
	GetAnimator()->PlayAnim(L"Title_Start", false, 1);
}

Title::~Title()
{
}

void Title::Update()
{
	if (KEY_DOWN(KEY_TYPE::DOWN) && index < 2)
		index += 1;
	if (KEY_DOWN(KEY_TYPE::UP) && index > 0)
		index -= 1;


	if (index != curIndex)
		switch (index)
		{
		case 0:
			GetAnimator()->PlayAnim(L"Title_Start", false, 1);
			curIndex = 0;
			break;
		case 1:
			GetAnimator()->PlayAnim(L"Title_GameRule", false, 1);
			curIndex = 1;
			break;
		case 2:
			GetAnimator()->PlayAnim(L"Title_Exit", false, 1);
			curIndex = 2;
			break;
		default:
			break;
		}



	GetAnimator()->Update();
}

void Title::Render(HDC _dc)
{
	Component_Render(_dc);
}
