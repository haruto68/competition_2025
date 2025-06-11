#pragma once
#include "../../Resource/ResourceManager.h"
class Score
{
protected:

private:
	static int stagelevel;		// ��p(�\���̂ł���p�\)
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
	void Initialize();			//����������
	void Update();				//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I������	

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