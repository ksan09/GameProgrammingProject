#pragma once
#include "GroundCollider.h"
class BoundGroundCollider :
    public GroundCollider
{
public:
    BoundGroundCollider();
    ~BoundGroundCollider();
public:
    virtual void GroundCheck(Rigidbody2D* rb) override;

    void Update() override;
private:
    float m_jumpValue;
    bool m_isDie;

};

