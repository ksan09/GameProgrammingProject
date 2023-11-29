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
public:
    void SetIsJump(bool v) { m_isJump = v; }
    void SetIsDoubleJump(bool v) { m_isDoubleJump = v; }
    const bool& GetDie() const { return m_isDie; }
    void Jump();
    void Die();
private:
    void DoubleJump();
private:
    Texture* m_pTex;
private:
    bool m_isDie;
    bool m_isPlayDieAnim;
    bool m_isJump;
    bool m_isDoubleJump;
    bool m_isRight;
    bool m_isSlowMove;
private:
    float m_fCurTime;
};

