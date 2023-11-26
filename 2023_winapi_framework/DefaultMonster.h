#pragma once
#include "Object.h"
#include "Block.h"
#include "Texture.h"
class BoundGroundCollider;
class DefaultMonster :
    public Block
{
public:
    DefaultMonster();
    ~DefaultMonster();
public:
    virtual void EnterCollision(Collider* _pOther) override;
public:
    void Update() override;
private:
    bool m_isDie;
    BoundGroundCollider* m_pBottomCol;
};

