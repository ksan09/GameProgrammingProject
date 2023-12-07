#pragma once
#include "Object.h"
#include "Block.h"
#include "Texture.h"
#include "Rigidbody2D.h"
class BoundGroundCollider;
class BulletMonster
	: public Block
{
public:
	BulletMonster();
	~BulletMonster();
public:
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void ExitCollision(Collider* _pOther) override;
public:
	void Update() override;
    void SpawnBullet();
public:
    void SetSpeed(float value)
    {
        Rigidbody2D* rb = GetRigidbody2D();
        if (rb == nullptr)
            return;

        m_speed = value;
        GetRigidbody2D()->SetVelocity({ value, rb->GetVelocity().y });
    };
    void SetDir(bool b)
    {
        m_bDir = b;
    }
private:
    float m_fCurTime;
    float m_fSpawnTime;
    float m_speed;
    bool m_isDie;
    bool m_bDir;
    BoundGroundCollider* m_pBottomCol;
};

