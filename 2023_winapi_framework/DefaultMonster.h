#pragma once
#include "Object.h"
#include "Block.h"
#include "Texture.h"
#include "Rigidbody2D.h"
class BoundGroundCollider;
class DefaultMonster :
    public Block
{
public:
    DefaultMonster();
    ~DefaultMonster();
public:
    virtual void EnterCollision(Collider* _pOther) override;
    virtual void ExitCollision(Collider* _pOther) override;
public:
    void Update() override;
public:
    void SetSpeed(float value) 
    { 
        Rigidbody2D* rb = GetRigidbody2D();
        if (rb == nullptr)
            return;

        m_speed = value; 
        GetRigidbody2D()->SetVelocity({ value, rb->GetVelocity().y });
    };
private:
    float m_speed;
    bool m_isDie;
    BoundGroundCollider* m_pBottomCol;
};

