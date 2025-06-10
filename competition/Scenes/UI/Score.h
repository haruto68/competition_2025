#pragma once
#include "../../Resource/ResourceManager.h"
class Score
{
protected:

private:
	static int stagelevel;		// 代用(構造体でも代用可能)
	static int power;
	static int hp;
	static int speed;
	static int cool_time;
	static int hit_range;
	static int three_way;
	static int level;
	// static int bullet_speed;

public:
	Score();
	~Score();

public:
	void Initialize();			//初期化処理
	void Update();				//更新処理
	void Draw() const;			//描画処理
	void Finalize();			//終了処理	

	static void SetStageLevel(int level)
	{
		stagelevel = level;
	}

	static int GetStageLevel()
	{
		return stagelevel;
	}


	static void SetPlayerStats(int p_level, int p_hp, int p_power, int p_speed, int p_cooltime, int p_hitrange, int p_threeway)
	{
		power = p_hp;
		hp = p_power;
		speed = p_speed;
		cool_time = p_cooltime;
		hit_range = p_hitrange;
		three_way = p_threeway;
		level = p_level;
	}

	static int GetPlayerStats()
	{
		return power, hp, speed, cool_time, hit_range, three_way, level;
	}
};