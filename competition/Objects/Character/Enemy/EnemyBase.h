#pragma once

#include"../Character.h"
#include"../../Shot/EnemyShot/EnemyShot.h"
#include"../../../Utility/InputManager.h"
#include"../../Item/ExperiencePoints/ExperiencePoints.h"

class EnemyBase : public Character
{
public:

	float shot_timer = 0.0f;       //時間経過
	float shot_cooldown = 2.0f;    //クールタイム

	int image;
	float radian = 0;

};