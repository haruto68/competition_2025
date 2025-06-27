#pragma once
#include"../SceneBase.h"
#include"../UI/Score.h"
#include"../RankingScene/RankingScene.h"

#define MAX_STAGE		(4)			// ゲームの最大ステージ数

class ResultScene : public SceneBase
{
protected:
	enum class selectedbutton 
	{
		Title,
		End
	};

	selectedbutton m_selectedbutton;
public:
	ResultScene();
	~ResultScene();

public:
	int menu_num;
	bool is_button;
	int back_ground_sound;
	int sounds_effect[2];
	int back_ground_image;
	Vector2D back_ground_location;		// 背景座標
	int power_icon[6];					// 強化	アイコン
	int window;							// 枠
	// リザルトシーンからのスコアの情報を入れる変数
	int level;
	int stagelevel;
	int power;
	int speed;
	int cool_time;
	int hit_range;
	bool three_way;
	bool drone;
	//int hp;

	bool is_drone;				// ドローンが取得されていたか
	bool is_max;				// 上限に行ったか
	bool is_check;				
	int color;					// 色変更
	bool is_cir;
	bool is_flash;				// 点滅させる
	float flash_timer;

	int circle;				// (カーソル)円の座標

	Vector2D button_location;			// ボタンの座標

	Score* score;
	RankingScene* ranking;

	// std::vector<int> font_name;					// フォント設定
	int font[5];								// フォントの設定

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

public:
	void CheckData();				// プレイヤーの情報がマイナスになっていないか確認する処理

	 void Cursor();				// カーソルの処理
};