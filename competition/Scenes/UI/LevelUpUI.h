#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"
#include"../../Utility/InputManager.h"
#include"../../Objects/Character/Player/PlayerStats.h"

#define	LOT_MAX			(5)	//最大抽選数

#define	STATS_HP		(0)
#define STATS_DAMAGE	(1)
#define STATS_SPEED		(2)
#define WAPON_3WAY		(3)
#define WAPON_SIZE		(4)

class LevelUpUI
{
public:
	bool old_flag;
	int cursor;
private:
	//画像
	int window[4] = {};
	int power[5] = {};
	int power_icon[5] = {};

	ePowerUp lot[LOT_MAX] = {};			//強化内容抽選
	int lot_str[LOT_MAX] = {};			//強化内容文字
	int lot_icon[LOT_MAX] = {};			//強化内容アイコン


public:
	LevelUpUI();
	~LevelUpUI();

public:
	void Initialize();					//初期化処理
	void Update(bool flag);				//更新処理
	void Draw(PlayerStats stats) const;	//描画処理
	void Finalize();					//終了処理

	void Lottery(int* nums);			//抽選
	ePowerUp GetLottery();				//抽選内容取得
};