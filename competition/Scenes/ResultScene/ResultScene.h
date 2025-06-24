#pragma once
#include"../SceneBase.h"
#include"../UI/Score.h"
#include"../RankingScene/RankingScene.h"

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
	//int hp;
	//int cool_time;
	//int hit_range;
	//int three_way;
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
};