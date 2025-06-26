#include "Score.h"

// 代用(構造体で作成可能)
 int Score::stagelevel = 0;
 int Score::level = 0;
 int Score::power = 0;
 int Score::hp = 0;
 int Score::speed = 0;
 float Score::cool_time = 0;
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
	// 元のパワーが1だったため
	power = (p_power - 1);
}

void Score::SetPlayerSpeed(int p_speed)
{
	// 一回強化すると100増えるため＊二回目からは5ずつ増加する
	speed = ((p_speed / 5) - 19);
}

void Score::SetPlayerCoolTime(float p_cooltime)
{
	cool_time = p_cooltime;
}

void Score::SetPlayerHitRange(int p_hitrange)
{
	// 一回取得するごとに2.0ずつ増加するため
	hit_range = (p_hitrange / 2);
}

void Score::SetPlayerThreeWay(bool p_threeway)
{
	// 一回きりだから取得したらbool型(取得したか、取得していないか)
	// 一回取得するとLvMAX
	three_way = p_threeway;
}

void Score::SetPlayerDrone(int p_drone)
{
	// ドローンを選択した時にdrone_countを参照しているため、
	// 複数になっても何個取得したら確認可能けど破壊されたものもカウントする(一回取得するとLvMAX)
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
