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
	const Vec2& GetVelocity() const { return m_velocity; }
	void SetUseGravity(bool value) { m_gravity = value; }
	void SetVelocity(Vec2 _velocity) { m_velocity = _velocity; }

public:
	void Stop() { m_velocity = { 0.f, 0.f }; }
	void StopVeloX() { m_velocity.x = 0; }
	void StopVeloY() { m_velocity.y = 0; }

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

