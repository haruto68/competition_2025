#pragma once
#include"../../Utility/Singleton.h"
#include"../../Resource/ResourceManager.h"

class LevelUI
{
public:
	float level;						// レベルの量
private:
	std::vector<int> level_bar;			// レベル増加の画像
public:
	LevelUI();
	~LevelUI();

public:
	void Initialize();			//初期化処理
	void Update();				//更新処理
	void Draw() const;			//描画処理
	void Finalize();			//終了処理

};