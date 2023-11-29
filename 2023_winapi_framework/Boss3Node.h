#pragma once
#include "Node.h"
#include "Object.h"

class RandomPatternNode
	: public CompositeNode
{
	// ������ �������� 2�� �̻��� ������ �ʵ���
public:
	RandomPatternNode();
	~RandomPatternNode();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	int m_iSelect;
};

class BoundMonsterSpawnPattern1Node
	: public ActionNode
{
public:
	BoundMonsterSpawnPattern1Node(Object* owner, Object* target);
	~BoundMonsterSpawnPattern1Node();
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
	float m_fCurTime;
	float m_fSpawnDelay;
	int m_iCurSpawnCount;
	int m_iSpawnCount;
	float m_fDelayTime;
private:
	float m_fSpawnMonsterSpeed;
};

class Boss3Pattern2Node
	: public ActionNode
{
public:
	Boss3Pattern2Node();
	~Boss3Pattern2Node();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	float m_fDangerDelay;
	float m_fDelaySpikeSpawn;
	float m_fWaitSpikeDelete;
	float m_fCurTime;
	// �ٴڿ� ����ǥ��
	// ���ٴϴ� ���� 4���� ����
	// ����ǥ�� ���� �� 0.1�� �� ���� ����
	// 5�� ��ٸ� �� ���� ����
};

class MoveNode
	: public ActionNode
{
public:
	MoveNode(Object* owner, Vec2 endPos, float speed);
	~MoveNode();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	Object* m_pOwner;
	Vec2 m_vEndPos;
	float m_fSpeed;

};

class Boss3Pattern3Node
	: public ActionNode
{
public:
	Boss3Pattern3Node(Object* owner, Object* target);
	~Boss3Pattern3Node();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	void SpawnBullet();
private:
	Object* m_pOwner;
	Object* m_pTarget;
private:
	float m_fCurTime;
	float m_fShootDelay;
	int m_iBulletCount;
	int m_iCurShootCount;
	bool m_bSpikeSpawn;
};