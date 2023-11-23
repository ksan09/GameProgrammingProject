#pragma once
#include "Object.h"
class Texture;
class Player :
    public Object
{
public:
    Player();
    ~Player();
public:
    void Update() override;
    virtual void EnterCollision(Collider* _pOther) override;

    void Render(HDC _dc) override;
private:
    void Jump();
private:
    Texture* m_pTex;
};

