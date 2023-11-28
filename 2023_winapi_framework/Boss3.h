#pragma once
#include "Object.h"
#include "BehaviorTree.h"
class Texture;
class Boss3 :
    public Object
{
public:
    Boss3(Object* target);
    ~Boss3();
public:
    void Update() override;
    virtual void EnterCollision(Collider* _pOther) override;

    void Render(HDC _dc) override;
private:
    void Die();
private:
    Object* m_pTarget;
private:
    Texture* m_pTex;
    BehaviorTree* m_pTree;
    int m_iHp;
    float m_iCurTime;
    float m_iDamageDelayTime;
    bool m_isDamage;
};

