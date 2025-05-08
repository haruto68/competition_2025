#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"
#include"../../Utility/InputManager.h"

class LevelUpUI
{
public:
	bool old_flag;
	int cursor;
private:
	//画像
	int window[3] = {};
	int power[5] = {};
	int power_icon[5] = {};


	int lottery[3] = {};		//強化内容抽選
	int lottery_icon[3] = {};	//強化内容アイコン


public:
	LevelUpUI();
	~LevelUpUI();

public:
	void Initialize();			//初期化処理
	void Update(bool flag);		//更新処理
	void Draw() const;			//描画処理
	void Finalize();			//終了処理
};