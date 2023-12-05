#pragma once
#include "Object.h"
#include "Texture.h"
class Block :
    public Object
{
public:
    Block();
    virtual ~Block();
public:
    void Render(HDC _dc) override;
public:
    void SetBlock(Vec2 scale);
    void SetSize(int v) { m_iSize = v; }
protected:
    Texture* m_pTex;
    int m_iSize;

};

