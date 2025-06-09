#pragma once

#include"../GameObject.h"
#include"../GameObjectManager.h"

enum eShotType
{
	ePlayer1,
	ePlayer2,
	ePlayer3,
	eEnemy1,	//�^��
	eEnemy2,	//�^��
	eEnemy3,	//�^��
	eEnemy4,	//���@�_��
	eEnemy5,	//���@��_��(75.0f)
	eEnemy6,	//���@���_��(75.0f)
	eEnemy7,	//�ォ�牺�ɃJ�[�u
	eEnemy8,	//�������ɃJ�[�u
	eEnemy9,	//�O�l�O�l
	eEnemy10,	//���@��_��(150.0f)
	eEnemy11,	//���@���_��(150.0f)
	eEnemy12,	//���@��_��(225.0f)
	eEnemy13,	//���@���_��(225.0f)
	eEnemy14,	//���@�_��2
};

class Shot : public GameObject
{
protected:
	Vector2D velocity = 0.0f;
	int anime_count = 0;
	bool turn_flag[2] = { false,false };
	Vector2D turn_target[5] = {};

	eShotType shot_type;
	int shot_power = 0;

public:
	bool flip_flag = false;

	void SetShotType(eShotType type)
	{
		shot_type = type;
	}
	void SetShowPower(int power)
	{
		shot_power = power;
	}
	
};