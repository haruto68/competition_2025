#pragma once
#include"../SceneBase.h"
#include"../UI/LevelUpUI.h"
#include"../UI/HpUI.h"
#include"../UI/LevelUI.h"

#include"../../Objects/GameObject.h"
#include"../../Objects/Character/Player/Player.h"
#include"../../Objects/Character/Enemy/Enemy1/Enemy1.h"
#include"../../Objects/Character/Enemy/Enemy2/Enemy2.h"
#include"../../Objects/Character/Enemy/Enemy3/Enemy3.h"
#include"../../Objects/Shot/PlayerShot/PlayerShot.h"
#include"../../Objects/Shot/EnemyShot/EnemyShot.h"
#include"../../Objects/Item/ExperiencePoints/ExperiencePoints.h"

struct Planet
{
	float x;
	float y;
	double size;
	double angle;
	int image;
};

class InGameScene : public SceneBase
{
protected:

public:
	std::vector<GameObject*> scene_objects_list;//オブジェクトリスト
	class GameObjectManager* object_manager;	//オブジェクトマネージャーインスタンス
	class Player* player;						//プレイヤーインスタンス
	LevelUpUI* level_up_ui;						//レベルアップUI
	HpUI* hp_ui;								//HPUI
	LevelUI* level_ui;							//レベルUI

	int back_ground_image;						//背景画像
	Vector2D back_ground_location;				//背景座標
	int planets_image[4];						//惑星画像
	Planet pla1;								//惑星1
	Planet pla2;								//惑星2

	float spawn_timer;							//敵生成クールタイム
	bool level_up_flg;							//レベルアップフラグ
	bool time_stop;



public:
	InGameScene();	//コンストラクタ
	~InGameScene();	//デストラクタ

public:
	virtual void Initialize() override;						//初期化処理
	virtual eSceneType Update(const float& delta_second);	//更新処理
	virtual void Draw() const override;						//描画処理
	virtual void Finalize() override;						//終了処理

public:
	virtual eSceneType GetNowSceneType() const override;	//現在シーン取得処理

private:
	void BackGroundManager(const float& delta_second);		//背景管理処理

	void EnemyManager(const float& delta_second);			//敵生成管理処理
	void Spawn();											//敵生成
};