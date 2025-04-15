#pragma once

#include"../Shot.h"

class EnemyShot : public Shot
{
protected:

private:
	float screen_velocity;		// スクリーン移動量

	int birth_count;

public:
	EnemyShot();
	~EnemyShot();

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