#pragma once
#include"../SceneBase.h"
#include"../UI/LevelUpUI.h"
#include"../UI/HpUI.h"
#include"../UI/LevelUI.h"
#include"../UI/Score.h"

#include"../../Objects/GameObject.h"
#include"../../Objects/Character/Player/Player.h"
#include"../../Objects/Character/Player/Drone.h"
#include"../../Objects/Character/Enemy/Enemy1/Enemy1.h"
#include"../../Objects/Character/Enemy/Enemy2/Enemy2.h"
#include"../../Objects/Character/Enemy/Enemy3/Enemy3.h"
#include"../../Objects/Character/Enemy/Enemy4/Enemy4.h"
#include"../../Objects/Character/Enemy/Enemy5/Enemy5.h"
#include"../../Objects/Character/Enemy/Enemy6/Enemy6.h"
#include"../../Objects/Character/Enemy/Enemy7/Enemy7.h"
#include"../../Objects/Character/Enemy/Enemy8/Enemy8.h"
#include"../../Objects/Character/Enemy/Enemy9/Enemy9.h"
#include "../../Objects/Character/Enemy/Boss1/Boss1.h"
#include "../../Objects/Character/Enemy/Boss2/Boss2.h"
#include "../../Objects/Character/Enemy/Boss3/Boss3.h"
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
	class Boss1* boss1;							//ボスインスタンス1
	class Boss2* boss2;							//ボスインスタンス2
	class Boss3* boss3;							//ボスインスタンス2
	class Drone* drone;							//ドローンインスタンス
	LevelUpUI* level_up_ui;						//レベルアップUI
	HpUI* hp_ui;								//HPUI
	LevelUI* level_ui;							//レベルUI
	Score* score;

	int stage_level;							//ステージレベル

	int back_ground_image[4];					//背景画像
	Vector2D back_ground_location;				//背景座標
	int planets_image[4];						//惑星画像
	Planet pla1;								//惑星1
	Planet pla2;								//惑星2
	bool back_ground_flag[2];

	int enemy_random;							//生成乱数
	int enemy_random_y;							//生成座標乱数
	float spawn_timer;							//敵生成クールタイム
	float pattern_timer;						//caseの時間経過
	bool boss_flag;								//ボス描画フラグ

	int player_old_level;						//プレイヤー過去レベル
	int up_grade_stock;							//アップグレードストック
	bool level_up_flg;							//レベルアップフラグ
	bool time_stop;								//一時停止フラグ
	float time_count;							//時間カウント
	int bgm[3];									//BGM
	int soundseffect[10];						//SE
	int dark_alpha;								//画面暗転アルファ値
	int pause_cursor;							//ポーズカーソル番号
	bool se_flg;
	int hp_bar[2];
	int button_sound[2];

	// std::vector<int> font_name;					// フォント設定
	int font[5];									// フォント設定


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
	void TestSpawn();										//テスト生成
	void Spawn1();											//雑魚生成1
	void Spawn2();											//雑魚生成2
	void Spawn3();											//雑魚生成3
	void BossManager();										//ボス生成管理処理

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
};