#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"

class HpUI
{
private:

public:
	HpUI();
	~HpUI();

public:
	void Initialize();			//‰Šú‰»ˆ—
	void Update(bool flag);		//XVˆ—
	void Draw() const;			//•`‰æˆ—
	void Finalize();			//I—¹ˆ—
};