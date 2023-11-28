#pragma once
#include "Object.h"
class Texture;
class Bullet :
    public Object
{
public:
    Bullet();
    ~Bullet();
public:
    void Update() override;
    void Render(HDC _dc) override;

    virtual void EnterCollision(Collider* _pOther) override;
private:
    Texture* m_pTex;
    bool m_isDie;
};

