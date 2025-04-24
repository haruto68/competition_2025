#pragma once

#include"../Character.h"
#include"../../Shot/PlayerShot/PlayerShot.h"
#include"PlayerStats.h"

class Player : public Character
{
protected:

private:
	float screen_velocity;		// ƒXƒNƒŠ[ƒ“ˆÚ“®—Ê

	class GameObjectManager* object_manager;

	float shot_timer;
	const float SHOT_INTERVAL;

	PlayerStats player_stats = {};

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

	void AddExperience(int exp);
	void LevelUp();

	void SetObjectList(GameObjectManager* object_manager)
	{
		this->object_manager = object_manager;
	}

	void SetPlayerStats(float attack, int life, int level)
	{
		player_stats.attack_power = attack;
		player_stats.life_count = life;
		player_stats.player_level = level;
	}
	PlayerStats GetPlayerStats() const
	{
		return player_stats;
	}
};