#pragma once
enum ePowerUp
{
	eHp,
	eDamage,
	eSpeed
};

struct PlayerStats
{
	float attack_power = 1.0f;
	float move_speed = 0.0f;
	int life_count = 3;
	int Shield_count = 3;
	int player_level = 1;

	// åoå±ílä÷òA
	int current_exp = 0;
	int next_level_exp = 100;
};
