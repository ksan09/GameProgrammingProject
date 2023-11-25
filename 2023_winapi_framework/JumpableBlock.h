#pragma once
#include "Object.h"
#include "Block.h"
#include "Texture.h"
class JumpableBlock :
    public Block
{
public:
    JumpableBlock();
    ~JumpableBlock();
public:
    void EnterCollision(Collider* _pOther) override;
public:
    void Update() override;
private:
    bool m_isDie;
};

