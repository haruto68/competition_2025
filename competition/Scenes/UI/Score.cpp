#include "Score.h"

// ë„óp(ç\ë¢ëÃÇ≈çÏê¨â¬î\)
 int Score::stagelevel = 0;
 int Score::level = 0;
 int Score::power = 0;
 int Score::hp = 0;
 int Score::speed = 0;
 int Score::cool_time = 0;
 int Score::hit_range = 0;
 bool Score::three_way = false;
 int  Score::drone = 0;
 // int Score::bullet_speed = 0;

Score::Score()
{
	
}

Score::~Score()
{

}

void Score::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
}

void Score::Update()
{

}

void Score::Draw() const
{
	
}

void Score::Finalize()
{

}

void Score::SetPlayerLevel(int p_level)
{
	level = p_level;
}

void Score::SetPlayerHp(int p_hp)
{
	hp = p_hp;
}

void Score::SetPlayerPower(int p_power)
{
	power = p_power;
}

void Score::SetPlayerSpeed(int p_speed)
{
	speed = p_speed;
}

void Score::SetPlayerCoolTime(int p_cooltime)
{
	cool_time = (p_cooltime + 1);
	// cool_time = (p_cooltime * 100);
}

void Score::SetPlayerHitRange(int p_hitrange)
{
	hit_range = p_hitrange;
}

void Score::SetPlayerThreeWay(bool p_threeway)
{
	three_way = p_threeway;
}

void Score::SetPlayerDrone(int p_drone)
{
	drone = p_drone;
}

int Score::SetPlayerHp()
{
	return hp;
}

int Score::GetPlayerLevel()
{
	return level;
}

int Score::GetPlayerPower()
{
	return power;
}

int Score::GetPlayerSpeed()
{
	return speed;
}

int Score::GetPlayerCoolTime()
{
	return cool_time;
}

int Score::GetPlayerHitRange()
{
	return hit_range;
}

bool Score::GetPlayerThreeWay()
{
	return three_way;
}

int Score::GetPlayerDrone()
{
	return drone;
}
