#pragma once

#include"../Character.h"
#include"../../Shot/PlayerShot/PlayerShot.h"

class Player : public Character
{
protected:

private:
	float screen_velocity;		// ƒXƒNƒŠ[ƒ“ˆÚ“®—Ê

	class GameObjectManager* object_manager;

	float shot_timer;
	const float SHOT_INTERVAL;
	int shotmode[];

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

	void SetObjectList(GameObjectManager* object_manager)
	{
		this->object_manager = object_manager;
	}
};