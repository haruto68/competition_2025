#pragma once
enum ePowerUp
{
	eHp,
	eDamage,
	eSpeed,
	eShotspeed,
	eThreeway,
	eShot_HitRange,
	eDrone
};

struct PlayerStats
{
	float attack_power = 1.0f;
	float move_speed = 0.0f;
	float shot_speed = 0.3f;
	int shot_speed_cnt = 0;
	int life_count = 3;
	int Shield_count = 3;
	int player_level = 1;
	int player_hp_max = 6;
	float player_shot_hitrange_up = 0.0f;
	int drone_count = 0;
	int drone_hp = 0;
	bool threeway_flag = false;
	bool drone_flag = false;



	// �o���l�֘A
	int current_exp = 0;
	int next_level_exp = 100;
};
