#pragma once
#include "Object.h"
class GroundCollider :
    public Object
{
public:
    GroundCollider();
    virtual ~GroundCollider();
public:
    virtual void EnterCollision(Collider* _pOther) override;
    void Update() override;
public:
    void SetCollider(Object* owner, Vec2 scale, Vec2 offset);
    virtual void GroundCheck(Rigidbody2D* rb);
protected:
    Object* m_pOwner;
    friend class Object;

};

