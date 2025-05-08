#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"

class HpUI
{
private:
	int hp_table;
	int hp_bar;

public:
	HpUI();
	~HpUI();

public:
	void Initialize();			//‰Šú‰»ˆ—
	void Update();				//XVˆ—
	void Draw() const;			//•`‰æˆ—
	void Finalize();			//I—¹ˆ—
};