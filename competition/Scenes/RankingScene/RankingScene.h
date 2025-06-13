#pragma once
#include "../SceneBase.h"

#define RANKING_DATA	(3)

class RankingScene : public SceneBase
{
protected:

private:
	int back_ground_sound;	// BGM
	int sounds_effect[2];	// 効果音
	int score[RANKING_DATA];	// ランキングデータ
	int rank[RANKING_DATA];		// ランク
	int player_stats[8];		// プレイヤーステータス
	int back_ground_image;		// 背景画像
	Vector2D back_ground_location;		// 背景座標

public:
	RankingScene();
	~RankingScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

	void SetRank(int);		// ランキングの入れ替え

private:
	void SortData();		// データ入れ替え処理

public:
	void GetScoreNo3()
	{
		return/*score[2]*/;
	}
};