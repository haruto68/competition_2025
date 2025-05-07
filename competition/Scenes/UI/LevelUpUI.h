#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"

class LevelUpUI
{
	bool draw_flag;

	int window[3] = {};
	int power[5] = {};
	int power_icon[5] = {};

public:
	LevelUpUI();
	~LevelUpUI();

public:
	void Initialize();			//‰Šú‰»ˆ—
	void Update(bool flag);		//XVˆ—
	void Draw() const;			//•`‰æˆ—
	void Finalize();			//I—¹ˆ—
};