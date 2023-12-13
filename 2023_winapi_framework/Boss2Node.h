#pragma once
#include "Node.h"
#include "Object.h"

class RandomPatternNode2
	: public CompositeNode
{
	// 패턴이 연속으로 2번 이상은 나오지 않도록
public:
	RandomPatternNode2();
	~RandomPatternNode2();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	int m_iSelect;
};

class MoveNode2
	: public ActionNode
{
public:
	MoveNode2(Object* owner, Vec2 endPos, float speed);
	~MoveNode2();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	Object* m_pOwner;
	Vec2 m_vEndPos;
	float m_fSpeed;

};

class Boss2Pattern1Node
	: public ActionNode
{
public:
	Boss2Pattern1Node(Object* owner, Object* target);
	~Boss2Pattern1Node();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	void SpawnObject();
private:
	Object* m_pOwner;
	Object* m_pTarget;
private:
	float m_fCurTime;
	float m_fSpawnTime;
private:
	float m_fDangerDelay;
	float m_fWaitSpikeDelete;
private:
	bool m_bSpikeSpawn;
	bool m_isRight;
};

class Boss2Pattern2Node
	: public ActionNode
{
public:
	Boss2Pattern2Node(Object* owner, Object* target);
	~Boss2Pattern2Node();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	void SpawnBullet();
	void SpawnObject();
private:
	Object* m_pOwner;
	Object* m_pTarget;
private:
	float m_fCurTime;
private:
	float m_fShootDelay;
	int m_iBulletCount;
	int m_iCurShootCount;
};

class Boss2Pattern3Node
	: public ActionNode
{
public:
	Boss2Pattern3Node(Object* owner, Object* target);
	~Boss2Pattern3Node();
public:
	virtual void OnStart() override;
	virtual NODE_STATE OnUpdate() override;
	virtual void OnStop() override;
private:
	void SpawnObject();
	void SpawnBullet();
private:
	Object* m_pOwner;
private:
	float m_fCurTime;
	float m_fBulletTime;
	bool m_bSpawn;
	bool m_isRight;
	int m_iSpawnCount;
};
