#pragma once

#include"../Character.h"
#include"../../Shot/PlayerShot/PlayerShot.h"
#include "Drone.h"
#include"PlayerStats.h"

class Player : public Character
{
protected:
	bool is_dead;
	bool is_visible;
	int death_image_index;


private:
	float screen_velocity;		// スクリーン移動量

	float shot_timer;
	float SHOT_INTERVAL;
	float invincible_timer;

	PlayerStats player_stats = {};

	Drone* drone;
	Vector2D old_location[20];

	std::vector<int> normal_image;
	std::vector<int> dead_image;
	bool is_invincible;
	int soundseffect[4];

	float blink_timer;
	float blink_interval;

	float death_timer;
	int death_image_count;
	float death_animation_interval;

	float animation_timer;
	int animation_frame_index;
	float animation_interval;


public:

	bool death_animation_finished;

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
	void Animation(float);

	void AddExperience(float exp);
	void LevelUp();

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
	void CheckLevelUp();

	void StatsUp(ePowerUp powerup);
};