#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"

class LevelUpUI
{
	bool draw_flag;

	int window;
	int table_01;
	int header;

public:
	LevelUpUI();
	~LevelUpUI();

public:
	void Initialize();			//‰Šú‰»ˆ—
	void Update(bool flag);		//XVˆ—
	void Draw() const;			//•`‰æˆ—
	void Finalize();			//I—¹ˆ—
};