#pragma once
#include "Bullet.h"
class AutoBullet :
    public Bullet
{
public:
    AutoBullet(Object* target);
    ~AutoBullet();
public:
    void Update() override;
private:
    Object* m_pTarget;
    float m_fCurTime;
    float m_fTargetingTime;
    float m_fDeleteTime;
    bool m_isTargeting;
};

