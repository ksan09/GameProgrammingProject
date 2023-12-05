#pragma once
#include "Object.h"
#include "Texture.h"
#include "BehaviorTree.h"
class Boss1 :
    public Object
{
    //SINGLE(Boss1);
public:
    Boss1(Object* target);
    Boss1();
    ~Boss1();
public:
    void Update() override;
    virtual void EnterCollision(Collider* _pOther) override;
    virtual void ExitCollision(Collider* _pOther) override;

    void Render(HDC _dc) override;
public:
    const bool& GetGround() const { return m_isGround; }
private:
    void Die();
private:
    Object* m_pTarget;
private:
    Texture* m_pTex;
    BehaviorTree* m_pTree;
    int m_iHp;
    float m_iCurTime;
    float m_fDieTime;
    float m_iDelayTime;
    bool m_isDie;
    bool m_isDamage;
    bool m_isGround;
};

