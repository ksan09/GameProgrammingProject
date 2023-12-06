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
	SetBkMode(_dc, TRANSPARENT);
	Vec2 pos = GetPos();
	TextOut(_dc, pos.x, pos.y, m_wText.c_str(), m_wText.length());
}
