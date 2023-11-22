#pragma once
class Object;

class Rigidbody2D
{
public:
	Rigidbody2D();
	~Rigidbody2D();
public:
	void LateUpdate();

public:
	void SetUseGravity(bool value) { m_gravity = value; }
	void SetVelocity(Vec2 _velocity) { m_velocity = _velocity; }
	void Stop() { m_velocity = { 0.f, 0.f }; }

private:
	void GroundCheck();
	void FallGravity();
	void CalculatePos();

private:
	bool m_useGravity;
	bool m_isFalling;
	bool m_isGrounded;

private:
	float m_gravity;
	Vec2 m_velocity;
	Object* m_pOwner;
	friend class Object;


};

