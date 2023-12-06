#pragma once
#include "Object.h"
class TextObject :
    public Object
{
public:
    TextObject(wstring text);
    ~TextObject();
public:
    void Render(HDC _dc) override;
private:
    wstring m_wText;
};

