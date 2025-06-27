#pragma once
#include "../../Resource/ResourceManager.h"
#include "ScoreData.h"
// #define DEBUG_SCORE

class Score
{
protected:

private:
	static int stagelevel;
	static int level;
	static int power;
	//static int hp;
	static int speed;
	static int cool_time;
	static int hit_range;
	static bool three_way;
	static int drone;
	// static int bullet_speed;

	// ScoreData score = {};
public:
	Score();
	~Score();

public:
	void Initialize();			//����������
	void Update();				//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I������	

#ifdef DEBUG_SCORE
	// �X�R�A��ݒ肷��
	void SetScoreData(int stagelevel, int p_level)
	{
		score.stagelevel = stagelevel;
		score.hp = p_level;
	}

	// �X�R�A���擾����
	ScoreData GetScoreData() const
	{
		return score;
	}

#endif // DEBUG_SCORE
	
	// �X�e�[�W�̏���ݒ肷��
	static void SetStageLevel(int level)
	{
		stagelevel = level;
	}
	// �X�e�[�W�̏����擾����
	static int GetStageLevel()
	{
		return stagelevel;
	}


	//// �v���C���[�̏���ݒ肷��
	//static void SetPlayerStats(int p_level, int p_hp, int p_power, int p_speed, int p_cooltime, int p_hitrange, int p_threeway)
	//{
	//	power = p_hp;
	//	hp = p_power;
	//	speed = p_speed;
	//	cool_time = p_cooltime;
	//	hit_range = p_hitrange;
	//	three_way = p_threeway;
	//	level = p_level;
	//}
	//// �v���C���[�̏����擾����
	//static int GetPlayerStats()
	//{
	//	return power, hp, speed, cool_time, hit_range, three_way, level;
	//}

	// �v���C���[�̏���ݒ肷��
	static void SetPlayerLevel(int);
	//static void SetPlayerHp(int);
	static void SetPlayerPower(int);
	static void SetPlayerSpeed(int);
	static void SetPlayerCoolTime(int);
	static void SetPlayerHitRange(int);
	static void SetPlayerThreeWay(bool);
	static void SetPlayerDrone(int);

	// �v���C���[�̏����擾����
	//static int SetPlayerHp();
	static int GetPlayerLevel();
	static int GetPlayerPower();
	static int GetPlayerSpeed();
	static int GetPlayerCoolTime();
	static int GetPlayerHitRange();
	static bool GetPlayerThreeWay();
	static int GetPlayerDrone();

};