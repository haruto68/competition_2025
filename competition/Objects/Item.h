#pragma once

#include"../GameObject.h"
#include"../GameObjectManager.h"

class Item : public GameObject
{
protected:
	Vector2D velocity = 0.0f;
	int anime_count = 0;

public:
	bool flip_flag = false;
};