#pragma once

#include"../Character.h"
#include"../../Shot/EnemyShot/EnemyShot.h"
#include"../../../Utility/InputManager.h"
#include"../../Item/ExperiencePoints/ExperiencePoints.h"

class EnemyBase : public Character
{
public:
	int image;					//画像
	float radian = 0;			//角度

	int max_hp = 0;				//最大HP
	int ratio = 100;			//HP割合

	float shot_timer = 0.0f;	//時間経過
	float shot_cooldown = 1.5f;	//クールタイム
	int atack_pattern = 0;		//攻撃パターン

	float death_count = 10.0f;	//死ぬまでの時間
	bool death_flag = false;	//死

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	int hp_bar1 = rm->GetImages("Resource/Images/HPUi/Boss_HP_Bar_1.png")[0];
	int hp_bar2 = rm->GetImages("Resource/Images/HPUi/Boss_HP_Bar_3.png")[0];

	//音源取得
	int soundseffect[3] =
	{
		rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemybreak.mp3"),
		rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemyshot.mp3"),
		rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemy_dead_se.mp3")
	};

	int bomb_sound[4] =
	{
		rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/bomb1.mp3"),
		rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/bomb2.mp3"),
		rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/bomb3.mp3"),
		rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/bomb4.mp3")
	};
	int bomb_sound_volume[4] = { 200,200,200,200 };
};