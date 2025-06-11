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
	int level;
	int stagelevel;
	int power;
	int hp;
	int speed;
	int cool_time;
	int hit_range;
	int three_way;
	Score* score;
	RankingScene* ranking;

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;
};