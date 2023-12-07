#pragma once
#include "Node.h"
#include "Object.h"

class RandomPatternNode1
	: public CompositeNode
{
public:
	RandomPatternNode1();
	~RandomPatternNode1();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	int m_iSelect;
};

class BoundMonsterSpawnPattern1Node1
	: public ActionNode
{
public:
	BoundMonsterSpawnPattern1Node1(Object* owner, Object* target);
	~BoundMonsterSpawnPattern1Node1();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	void SpawnObject();
	void SpawnBullet();
private:
	Object* m_pOwner;
	Object* m_pTarget;
private:
	bool m_isRight;
	bool m_isDanger;
	float m_fDangerDelay;
	float m_fCurTime;
	float m_fCurTime2;
	float m_fSpawnDelay;
	int m_iCurSpawnCount;
	int m_iSpawnCount;
	float m_fDelayTime;
private:
	float m_fSpawnMonsterSpeed;
};

class Boss1Pattern2Node
	: public ActionNode
{
public:
	Boss1Pattern2Node(Object* Owner, Object* target);
	~Boss1Pattern2Node();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
	void OnShoot();
private:
	float m_fDangerDelay;
	float m_fDelaySpikeSpawn;
	float m_fWaitSpikeDelete;
	float m_fCurTime;
	Object* m_pOwner;
	Object* m_pSaveOwner;
	Object* m_pTarget;
	// 바닥에 위험표시
	// 떠다니는 몬스터 4마리 생성
	// 위험표시 제거 후 0.1초 후 가시 생성
	// 5초 기다린 후 가시 제거
};

class JumpNode
	: public ActionNode
{
public:
	JumpNode(Object* owner, Vec2 endPos, float speed);
	~JumpNode();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	Rigidbody2D* m_pRb;
	Object* m_pOwner;
	Vec2 m_vEndPos;
	float m_fDis;
	float m_fSpeed;
	float m_fCurTime;

};