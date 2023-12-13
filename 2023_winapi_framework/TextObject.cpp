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
	
	HFONT hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, L"DungGeunMo");
	SelectObject(_dc, hFont);

	SetBkMode(_dc, TRANSPARENT);
	Vec2 pos = GetPos();
	TextOut(_dc, pos.x - 10, pos.y, m_wText.c_str(), m_wText.length());
	DeleteObject(hFont);

}
