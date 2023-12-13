#include "pch.h"
#include "TextObject.h"

TextObject::TextObject(wstring text)
	: m_wText(text)
{
}

TextObject::~TextObject()
{
}

void TextObject::Render(HDC _dc)
{
	SetTextColor(_dc, RGB(0, 0, 0)); 

	HFONT hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, L"DungGeunMo");
	SelectObject(_dc, hFont);

	AddFontResourceW(L"Font\\DungGeunMo.ttf");

	SetBkMode(_dc, TRANSPARENT);
	SIZE textSize;
	GetTextExtentPoint32(_dc, m_wText.c_str(), m_wText.length(), &textSize);

	Vec2 pos = GetPos();
	pos.x -= textSize.cx / 2 - 30;  // Adjust the X position for center alignment
	pos.y -= textSize.cy / 2;  // Adjust the Y position for center alignment

	TextOut(_dc, static_cast<int>(pos.x), static_cast<int>(pos.y), m_wText.c_str(), m_wText.length());

	DeleteObject(hFont);
}
