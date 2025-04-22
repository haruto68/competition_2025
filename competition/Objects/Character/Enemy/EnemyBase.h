#pragma once

#include"../Character.h"
#include"../../Shot/EnemyShot/EnemyShot.h"
#include"../../../Utility/InputManager.h"

class EnemyBase : public Character
{
protected:
	class GameObjectManager* object_manager;
public:
	void SetObjectList(GameObjectManager* object_manager)
	{
		this->object_manager = object_manager;
	}

	float shot_timer = 0.0f;       //時間経過
	float shot_cooldown = 2.0f;    //クールタイム

};