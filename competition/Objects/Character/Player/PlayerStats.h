#pragma once

struct PlayerStats
{
	float base_speed;
	float attack_power;
	int life_count;
	int player_level;
	float speed_multiplier;

	// ŒoŒ±’lŠÖ˜A
	int current_exp = 0;
	int next_level_exp = 100;
};
