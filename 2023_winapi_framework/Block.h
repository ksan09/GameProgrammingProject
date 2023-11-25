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
protected:
    Texture* m_pTex;

};

