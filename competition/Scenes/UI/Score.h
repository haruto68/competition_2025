#pragma once
#include "../../Resource/ResourceManager.h"
class Score
{
protected:

private:
	static int stagelevel;		// 代用(構造体でも代用可能)
public:
	// int stagelevel = 0;
public:
	Score();
	~Score();

public:
	void Initialize();			//初期化処理
	void Update();				//更新処理
	void Draw() const;			//描画処理
	void Finalize();			//終了処理	

	static void SetStageLevel(int level)
	{
		stagelevel = level;
	}

	static int GetStageLevel()
	{
		return stagelevel;
	}
};