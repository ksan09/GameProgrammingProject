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
	Vec2 pos = GetPos();
	TextOut(_dc, pos.x - 10, pos.y, m_wText.c_str(), m_wText.length());
}
