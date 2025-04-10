#pragma once

#include"../Character.h"

class Player : public Character
{
protected:

private:
	float screen_velocity;		// ƒXƒNƒŠ[ƒ“ˆÚ“®—Ê

public:
	Player();
	~Player();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void Draw(const Vector2D&, bool) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObject*) override;

public:
	Vector2D GetScreenVelocity();
	Vector2D GetVelocity();
	void SetVelocity(Vector2D);

	void Movement(float);
	void Animation();
};