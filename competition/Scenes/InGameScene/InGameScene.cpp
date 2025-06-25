#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Objects/GameObjectManager.h"

#define TIME_SPEED	(1.0f)
// #define TIME_SPEED	(60.0f)

InGameScene::InGameScene() :
	object_manager(nullptr),
	player(),
	boss1(nullptr),
	boss2(nullptr),
	boss3(nullptr),
	drone(nullptr),
	level_up_ui(),
	hp_ui(),
	level_ui(),
	stage_level(1),
	back_ground_image(),
	back_ground_location(0),
	planets_image(),
	pla1(),
	pla2(),
	enemy_random(1),
	enemy_random_y(1),
	pattern_timer(0),
	spawn_timer(0),
	boss_flag(false),
	player_old_level(1),
	up_grade_stock(0),
	level_up_flg(),
	time_stop(),
	time_count(60),
	bgm(),
	soundseffect(),
	dark_alpha(600),
	pause_cursor(0),
	score(),
	font{}
{
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	screen_offset.x = -0.02f;

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	//背景
	back_ground_image[1] = rm->GetImages("Resource/Images/back_ground/universe_space02.png")[0];
	back_ground_image[2] = rm->GetImages("Resource/Images/back_ground/universe_space03.png")[0];
	back_ground_image[3] = rm->GetImages("Resource/Images/back_ground/universe_space05.png")[0];
	back_ground_location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);

	// 惑星
	planets_image[0] = rm->GetImages("Resource/Images/Planets/Planet1.png")[0];
	planets_image[1] = rm->GetImages("Resource/Images/Planets/Planet2.png")[0];
	planets_image[2] = rm->GetImages("Resource/Images/Planets/Planet3.png")[0];
	planets_image[3] = rm->GetImages("Resource/Images/Planets/Planet4.png")[0];
	pla1 = { D_WIN_MAX_X * 1.5,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
	pla1 = { D_WIN_MAX_X * 1.0,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };

	// 音源取得
	bgm[0] = rm->GetSounds("Resource/Sounds/BGM/InGame/GameMain_Stage1.mp3");
	bgm[1] = rm->GetSounds("Resource/Sounds/BGM/InGame/GameMain_Upgrade.mp3");

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{

	//GameObjectManagerインスタンス取得
	object_manager = new GameObjectManager();

	//プレイヤー生成
	player = object_manager->CreateGameObject<Player>(Vector2D(160, 360));

	//
	level_up_ui = new LevelUpUI();
	level_up_ui->Initialize();

	// Test用生成
	hp_ui = new HpUI();
	hp_ui->Initialize();

	level_ui = new LevelUI();
	level_ui->Initialize();

	score = new Score();
	score->SetStageLevel(stage_level);
	
	// 音源の音量の設定
	ChangeVolumeSoundMem(100, bgm[0]);
	// 音源の再生
	PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP, TRUE);
	
	/*object_manager->CreateGameObject<Boss1>(Vector2D(1200, 400));*/

		// フォントの登録
	// font_name.push_back(CreateFontToHandle("魔導太丸ゴシック", 70, 6));
	// font_name.push_back(CreateFontToHandle("魔導太丸ゴシック", 40, 6));
	// font_name.push_back(CreateFontToHandle("魔導太丸ゴシック", 50, 6));
	// font_name.push_back(CreateFontToHandle("魔導太丸ゴシック", 100, 6));
	// font_name.push_back(CreateFontToHandle("魔導太丸ゴシック", 80, 6));

	// フォントの登録
	font[0] = CreateFontToHandle("魔導太丸ゴシック", 40, 6);
	font[1] = CreateFontToHandle("魔導太丸ゴシック", 50, 6);
	font[2] = CreateFontToHandle("魔導太丸ゴシック", 70, 6);
	font[3] = CreateFontToHandle("魔導太丸ゴシック", 80, 6);
	font[4] = CreateFontToHandle("魔導太丸ゴシック", 100, 6);

}

eSceneType InGameScene::Update(const float& delta_second)
{
	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//入力情報の更新
	input->Update();

	//レベルアップUI更新処理
	level_up_ui->Update(level_up_flg, player->GetPlayerStats());


	level_ui->SetExperience(player->GetPlayerStats().current_exp, player->GetPlayerStats().next_level_exp);
	level_ui->Update();
	hp_ui->SetHp(player->GetPlayerStats().life_count, 6);


	// シーン内オブジェクト更新
	if(!time_stop)
	{
		//タイムカウント
		if (time_count > 50 && dark_alpha > 0)
		{
			dark_alpha--;
		}
		if(time_count >= 0.0f)
		{
			if (dark_alpha <= 0)
				time_count -= (delta_second * TIME_SPEED);
		}
		else
		{
			//ボス生成管理
			BossManager();
		}

		// 背景管理処理
		BackGroundManager(delta_second);

		// 敵生成管理処理
		if (dark_alpha <= 0)
			EnemyManager(delta_second);

		// 生成するオブジェクトの確認
		object_manager->CheckCreateObject();
		// 破棄するオブジェクトの確認
		object_manager->CheckDestroyObject();
		// 現在のオブジェクトリストを取得
		scene_objects_list = object_manager->GetObjectList();

		// リスト内のオブジェクトを更新する
		for (GameObject* obj : scene_objects_list)
		{
			//Update
			if (dark_alpha <= 0)
			{
				obj->Update(delta_second);
			}
			else if (obj->GetCollision().object_type != eObjectType::ePlayer)
			{
				obj->Update(delta_second);
			}
			else if (dark_alpha >= 255)
			{
				player->SetLocation(Vector2D(160, 360));
				if (drone != nullptr)
				{
					drone->SetLocation(Vector2D(player->GetLocation().x - 50, player->GetLocation().y));
				}
				
			}
			//爆発
			if (obj->GetExplosionFlag())
			{
				obj->Explosion(delta_second);
			}
			// プレイヤー座標受け渡し
			obj->SetPlayerLocation(player->GetLocation());
			//プレイヤーステータス受け渡し
			obj->SetPlayerStats(player->GetPlayerStats());
			// オブジェクトをスクロールと一緒に動かす処理
			if (obj->GetCollision().object_type != eObjectType::ePlayer)
			{
				//obj->SetLocation(Vector2D(obj->GetLocation().x + screen_offset.x, obj->GetLocation().y));
			}
			// オブジェクトマネージャーのインスタンス引き渡し
			if (obj->CheckInstance() == nullptr)
			{
				obj->SetInstance(object_manager);
			}
		}

		//当たり判定チェック処理
		if(dark_alpha <= 0)
		{
			for (int a = 0; a < scene_objects_list.size(); a++)
			{
				for (int b = a + 1; b < scene_objects_list.size(); b++)
				{
					object_manager->HitCheck(scene_objects_list[a], scene_objects_list[b]);
					object_manager->HitCheck(scene_objects_list[b], scene_objects_list[a]);
				}
			}
		}

		// 画面外へでたオブジェクトを破壊する
		for (GameObject* obj : scene_objects_list)
		{
			if (obj->GetLocation().x <= -640 || obj->GetLocation().x >= D_WIN_MAX_X + 650 ||
				obj->GetLocation().y <= -50 || obj->GetLocation().y >= D_WIN_MAX_Y + 50)
			{
				if (obj != boss3)
					object_manager->DestroyGameObject(obj);
			}
		}
	}
	else
	{
		if(level_up_flg == true)
		{
			//カーソル左
			if (input->GetKeyUp(KEY_INPUT_A) || input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
			{
				if (level_up_ui->cursor == 0)
					level_up_ui->cursor = 2;
				else if (level_up_ui->cursor == 1)
					level_up_ui->cursor = 0;
				else
					level_up_ui->cursor = 1;
			}
			//カーソル右
			if (input->GetKeyUp(KEY_INPUT_D) || input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
			{
				if (level_up_ui->cursor == 0)
					level_up_ui->cursor = 1;
				else if (level_up_ui->cursor == 1)
					level_up_ui->cursor = 2;
				else
					level_up_ui->cursor = 0;
			}
			//カーソル決定
			if (input->GetKeyUp(KEY_INPUT_E) || input->GetButtonDown(XINPUT_BUTTON_A))
			{
				//強化内容取得
				ePowerUp strengthen = level_up_ui->GetLottery();
				//強化
				player->StatsUp(strengthen);
				time_stop = false;
				level_up_flg = false;

				up_grade_stock--;
			}
		}
		else
		{
			//カーソル上
			if (input->GetKeyUp(KEY_INPUT_W) || input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))
			{
				if (pause_cursor == 1)
					pause_cursor = 0;
			}
			//カーソル下
			if (input->GetKeyUp(KEY_INPUT_S) || input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
			{
				if (pause_cursor == 0)
					pause_cursor = 1;
			}
			//カーソル決定
			if (input->GetKeyUp(KEY_INPUT_E) || input->GetButtonDown(XINPUT_BUTTON_A))
			{
				
				if (pause_cursor == 0)
				{
					time_stop = false;
				}
				else
				{
					return eSceneType::eTitle;
				}
			}
		}
	}

	//ポーズ画面
	if (((input->GetKeyUp(KEY_INPUT_TAB) ||
		input->GetButtonDown(XINPUT_BUTTON_START)))
		&& level_up_flg == false && dark_alpha <= 0
		&& player->GetPlayerStats().life_count > 0)
	{
		pause_cursor = 0;
		if (time_stop)
			time_stop = false;
		else
			time_stop = true;
	}

	//アップグレード
	if (((input->GetKeyUp(KEY_INPUT_L) ||
		input->GetButtonDown(XINPUT_BUTTON_Y))
		&& time_stop == false)
		/*&& up_grade_stock > 0*/ && dark_alpha <= 0
		&& player->GetPlayerStats().life_count > 0)
	{
		level_up_flg = true;
		time_stop = true;
	}
	//レベルアップ時
	if (player->GetPlayerStats().player_level != player_old_level)
	{
		up_grade_stock++;
	}
	player_old_level = player->GetPlayerStats().player_level;
	
	//リザルトシーンへ遷移
	if (input->GetKeyUp(KEY_INPUT_SPACE) ||
		player->GetPlayerStats().life_count <= 0 && player->death_animation_finished ||
		stage_level == 4)
	{
		// プレイヤーの情報を取得する
		//score->SetPlayerStats(player->GetPlayerStats().player_level, player->GetPlayerStats().life_count, player->GetPlayerStats().attack_power, player->GetPlayerStats().move_speed, player->GetPlayerStats().shot_speed, player->GetPlayerStats().player_shot_hitrange_up, player->GetPlayerStats().threeway_flag);
		score->SetPlayerLevel(player->GetPlayerStats().player_level);
		score->SetPlayerPower(player->GetPlayerStats().attack_power);
		score->SetPlayerSpeed(player->GetPlayerStats().move_speed);
		score->SetPlayerCoolTime(player->GetPlayerStats().shot_speed);
		return eSceneType::eResult;
	}	

	//ゲームを終了
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	// 背景描画	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
	DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image[stage_level], TRUE);
	DrawRotaGraphF(back_ground_location.x + D_WIN_MAX_X, back_ground_location.y, 1.0, 0.0, back_ground_image[stage_level], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 惑星描画
	int bright = 125;
	SetDrawBright(bright, bright, bright);
	DrawRotaGraphF(pla1.x, pla1.y, pla1.size, pla1.angle, pla1.image, TRUE);
	DrawRotaGraphF(pla2.x, pla2.y, 0.5, 0.0, pla2.image, TRUE);
	SetDrawBright(255, 255, 255);

	int c = 0;
	// オブジェクト描画
	for (GameObject* obj : scene_objects_list)
	{
		if(!obj->GetExplosionFlag())
			obj->Draw(screen_offset, false);
		else
			obj->DrawExplosion();
		c++;
	}
	//オブジェクト数描画
	//DrawFormatString(1100, 100, GetColor(255, 255, 255), "%d", c);

	////////////////////////////////////////////////////////////////////////////////////////////////////

	//UIゾーン
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, 1280, 80, GetColor(50, 0, 100), TRUE);
	DrawBox(0, 680, 1280, 720, GetColor(50, 0, 100), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	char buf[128];		// textを格納する変数

	//タイムカウント
	SetFontSize(70);
	if (time_count > 0)
	{
		// DrawFormatString(1100, 10, GetColor(255, 255, 255), "%.1f", time_count);
		snprintf(buf, sizeof(buf), "%.1f", time_count);
		// DrawStringToHandle(1100, 10, buf, GetColor(255, 255, 255), font_name[0]);
		DrawStringToHandle(1100, 10, buf, GetColor(255, 255, 255), font[3]);
	}
	//ステージレベル
	SetFontSize(40);
	// DrawFormatString(570, 20, GetColor(255, 255, 255), "Stage");
	// DrawStringToHandle(570, 20, "Stage", GetColor(255, 255, 255), font_name[1]);
	DrawStringToHandle(570, 20, "STAGE", GetColor(255, 255, 255), font[0]);
	int level_color = 0;
	if (stage_level == 1)
		level_color = GetColor(50, 255, 50);
	else if (stage_level == 2)
		level_color = GetColor(255, 255, 50);
	else if (stage_level == 3)
		level_color = GetColor(255, 50, 50);
	SetFontSize(50);
	// DrawFormatString(700, 15, level_color, "%d", stage_level);
	snprintf(buf, sizeof(buf), "%d", stage_level);
	// DrawStringToHandle(700, 15, buf, GetColor(255, 255, 255), font_name[2]);

	switch (stage_level)
	{
	case 1:
		DrawStringToHandle(700, 15, buf, GetColor(50, 255, 50), font[1]);
		break;
	case 2:
		DrawStringToHandle(700, 15, buf, GetColor(255, 255, 50), font[1]);
		break;
	case 3:
		DrawStringToHandle(700, 15, buf, GetColor(255, 50, 50), font[1]);
		break;
	default:
		break;
	}

	// プレイヤーのHPのテーブルHPバーの描画
	hp_ui->Draw();
	// レベルUIバーの描画
	level_ui->Draw();

	if (up_grade_stock > 0)
	{
		SetFontSize(40);
		// DrawFormatString(476, 681, GetColor(0, 0, 0), "Y_button to UpGrade");
		// DrawFormatString(475, 680, GetColor(125, 0, 175), "Y_button to UpGrade");
		// DrawStringToHandle(475, 680, "Y_button to UpGrade", GetColor(0, 0, 0), font_name[1]);
		// DrawStringToHandle(475, 681, "Y_button to UpGrade", GetColor(125, 0, 175), font_name[1]);
		DrawStringToHandle(475, 680, "Y_button to UpGrade", GetColor(0, 0, 0), font[0]);
		DrawStringToHandle(475, 681, "Y_button to UpGrade", GetColor(125, 0, 175), font[0]);
		if(up_grade_stock > 1)
		{
			// DrawFormatString(900, 680, GetColor(0, 0, 0), "× %d", up_grade_stock);
			// DrawFormatString(901, 681, GetColor(125, 0, 175), "× %d", up_grade_stock);
			snprintf(buf, sizeof(buf), "× %d", up_grade_stock);
			// DrawStringToHandle(900, 680, buf, GetColor(0, 0, 0), font_name[1]);
			// DrawStringToHandle(901, 681, buf, GetColor(125, 0, 175), font_name[1]);
			DrawStringToHandle(900, 680, buf, GetColor(0, 0, 0), font[0]);
			DrawStringToHandle(901, 681, buf, GetColor(125, 0, 175), font[0]);
		}
	}

	//ポーズ画面描画
	if (time_stop == true && level_up_flg == false)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetFontSize(100);
		// DrawFormatString(425, 125, GetColor(255, 255, 255), "P A U S E");
		// DrawStringToHandle(425, 125, "P A U S E", GetColor(255, 255, 255), font_name[3]);
		DrawStringToHandle(425, 125, "P A U S E", GetColor(255, 255, 255), font[4]);
		// int pause_font[2] = { 40,40 };
		// if(pause_cursor == 0)
		// 	pause_font[0] = 80;
		// else if(pause_cursor == 1)
		// 	pause_font[1] = 80;

		// SetFontSize(pause_font[0]);
		// DrawFormatString(500, 350, GetColor(255, 255, 255), "B A C K");
		// SetFontSize(pause_font[1]);
		// DrawFormatString(475, 500, GetColor(255, 255, 255), "T I T L E");
		switch (pause_cursor)
		{
			case 0:
				// DrawStringToHandle(500, 350, "B A C K", GetColor(255, 255, 255), font_name[4]);
				// DrawStringToHandle(475, 500, "T I T L E", GetColor(255, 255, 255), font_name[1]);
				DrawStringToHandle(515, 350, "B A C K", GetColor(255, 255, 255), font[3]);
				DrawStringToHandle(565, 500, "T I T L E", GetColor(255, 255, 255), font[0]);
				break;
			case 1:
				DrawStringToHandle(580, 350, "B A C K", GetColor(255, 255, 255), font[0]);
				DrawStringToHandle(480, 500, "T I T L E", GetColor(255, 255, 255), font[3]);
				break;
			default:
				break;
		}
	}


	//レベルアップUI描画
	level_up_ui->Draw(level_up_flg, time_stop);

	////////////////////////////////////////////////////////////////////////////////////////////////////

	//暗転
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, dark_alpha);
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//ゲーム開始
	if (dark_alpha > 300)
	{
		SetFontSize(100);
		// DrawFormatString(425, 300, GetColor(255, 255, 255), "STAGE 1");
		// DrawStringToHandle(425, 300, "STAGE 1", GetColor(255, 255, 255), font_name[3]);
		DrawStringToHandle(425, 300, "STAGE 1", GetColor(255, 255, 255), font[4]);
	}

	//ステージ遷移1>>2
	if (boss1 != nullptr && stage_level == 1)
	{
		if (boss1->GetBoss1DeathCount() < 3.0f && boss1->GetBoss1DeathCount() > 1.5f)
		{
			SetFontSize(70);
			// DrawFormatString(425, 260, GetColor(255, 255, 255), "STAGE CLEAR");
			// DrawStringToHandle(425, 260, "STAGE CLEAR", GetColor(255, 255, 255), font_name[0]);
			DrawStringToHandle(425, 260, "STAGE CLEAR", GetColor(255, 255, 255), font[2]);
		}
		else if (boss1->GetBoss1DeathCount() < 1.1 && boss1->GetBoss1DeathCount() > 0.0f)
		{
			SetFontSize(100);
			// DrawFormatString(425, 300, GetColor(255, 255, 255), "STAGE 2");
			// DrawStringToHandle(425, 300, "STAGE 2", GetColor(255, 255, 255), font_name[3]);
			DrawStringToHandle(425, 300, "STAGE 2", GetColor(255, 255, 255), font[4]);
		}
	}
	//ステージ遷移2>>3
	if (boss2 != nullptr && stage_level == 2)
	{
		if (boss2->GetBoss2DeathCount() < 3.0f && boss2->GetBoss2DeathCount() > 1.5f)
		{
			SetFontSize(70);
			// DrawFormatString(425, 260, GetColor(255, 255, 255), "STAGE CLEAR");
			// DrawStringToHandle(425, 260, "STAGE CLEAR", GetColor(255, 255, 255), font_name[0]);
			DrawStringToHandle(425, 260, "STAGE CLEAR", GetColor(255, 255, 255), font[2]);

		}
		else if (boss2->GetBoss2DeathCount() < 1.1 && boss2->GetBoss2DeathCount() > 0.0f)
		{
			SetFontSize(100);
			// DrawFormatString(425, 300, GetColor(255, 255, 255), "STAGE 3");
			DrawStringToHandle(425, 260, "STAGE 3", GetColor(255, 255, 255), font[4]);
		}
	}
	//ステージ遷移3>>クリア
	if (boss3 != nullptr && stage_level == 3)
	{
		if (boss3->GetBoss3DeathCount() < 3.0f && boss3->GetBoss3DeathCount() > 1.5f)
		{
			SetFontSize(70);
			// DrawFormatString(425, 260, GetColor(255, 255, 255), "STAGE CLEAR");
			DrawStringToHandle(425, 260, "STAGE CLEAR", GetColor(255, 255, 255), font[2]);
		}
		else if (boss3->GetBoss3DeathCount() < 1.1 && boss3->GetBoss3DeathCount() > 0.0f)
		{
			SetFontSize(100);
			// DrawFormatString(375, 300, GetColor(255, 255, 255), "GAME CLEAR");
			DrawStringToHandle(375, 360, "GAME CLEAR", GetColor(255, 255, 255), font[4]);
		}
	}

	//エネミーランダム確認用
	//DrawFormatString(1100, 100, GetColor(255, 255, 255), "%d", enemy_random);
}

void InGameScene::Finalize()
{
	level_up_ui->Finalize();
	hp_ui->Finalize();
	level_ui->Finalize();
	StopSoundMem(bgm[0]);
	StopSoundMem(bgm[1]);

	// 設定したフォントを削除する
	for (int i = 0; i < 5; i++)
	{
		DeleteFontToHandle(font[i]);
	}
}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}

void InGameScene::BackGroundManager(const float& delta_second)
{
	float speed = 1000;
	// 背景ループ
	back_ground_location.x -= 0.04f * delta_second * speed;
	if (back_ground_location.x <= -(D_WIN_MAX_X / 2))
		back_ground_location.x = D_WIN_MAX_X / 2;
	speed = 300;
	// 惑星ループ1
	pla1.x -= 0.5 * delta_second * speed;
	if (pla1.x <= -(D_WIN_MAX_X / 2))
	{
		pla1 = { D_WIN_MAX_X * 1.5,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
	}
	// 惑星ループ2
	pla2.x -= 0.5 * delta_second * speed;
	if (pla2.x <= -(D_WIN_MAX_X / 2))
	{
		pla2 = { D_WIN_MAX_X * 1.5,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
	}
}

void InGameScene::EnemyManager(const float& delta_second)
{
	// 敵生成クールタイム
	spawn_timer += delta_second;

	if (boss_flag == false)
	{
		//レベル1
		if (stage_level == 1)
		{
			if (spawn_timer >= 1.0f)
			{
				pattern_timer += delta_second;
			}
			if (spawn_timer >= 5.0f)
			{
				spawn_timer = 0.0f;
				enemy_random = rand() % 3 + 1;
				pattern_timer = 0.0f;
			}
			Spawn1();
		}
		//レベル2
		if (stage_level == 2)
		{
			if (spawn_timer >= 1.0f)
			{
				pattern_timer += delta_second;
			}
			if(spawn_timer >= 5.0f)
			{
				spawn_timer = 0.0f;
				enemy_random = rand() % 3 + 1;
				enemy_random_y = rand() % 4 + 1;
				pattern_timer = 0.0f;
			}
			Spawn2();
		}
		//レベル3
		if (stage_level == 3)
		{
			if (spawn_timer >= 1.0f)
			{
				pattern_timer += delta_second;
			}
			if (spawn_timer >= 5.0f)
			{
				spawn_timer = 0.0f;
				enemy_random = rand() % 5 + 1;
				enemy_random_y = rand() % 4 + 1;
				pattern_timer = 0.0f;
			}
			Spawn3();
		}
	}
	TestSpawn();
}

//テストスポーン
void InGameScene::TestSpawn()
{
	int y_top = 95;
	int y_center = 380;
	int y_botom = 665;

	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyUp(KEY_INPUT_1))
		object_manager->CreateGameObject<Enemy1>(Vector2D(1300, y_center));
	else if (input->GetKeyUp(KEY_INPUT_2))
		object_manager->CreateGameObject<Enemy2>(Vector2D(1300, y_top))->SetTrans();
	else if (input->GetKeyUp(KEY_INPUT_3))
		object_manager->CreateGameObject<Enemy2>(Vector2D(1300, y_botom));
	else if (input->GetKeyUp(KEY_INPUT_4))
		object_manager->CreateGameObject<Enemy3>(Vector2D(1300, y_center));
	else if (input->GetKeyUp(KEY_INPUT_5))
		object_manager->CreateGameObject<Enemy4>(Vector2D(1300, y_center));
	else if (input->GetKeyUp(KEY_INPUT_6))
		object_manager->CreateGameObject<Enemy5>(Vector2D(1300, y_center));
	else if (input->GetKeyUp(KEY_INPUT_7))
		object_manager->CreateGameObject<Enemy6>(Vector2D(1300, y_center));
	else if (input->GetKeyUp(KEY_INPUT_8))
		object_manager->CreateGameObject<Enemy7>(Vector2D(1200, y_center));
	else if (input->GetKeyUp(KEY_INPUT_9))
		object_manager->CreateGameObject<Enemy8>(Vector2D(1200, y_center));
	else if (input->GetKeyUp(KEY_INPUT_0))
		object_manager->CreateGameObject<Enemy9>(Vector2D(1200, y_center));
}

//雑魚生成1
void InGameScene::Spawn1()
{
	int y_top = 95;
	int y_center = 380;
	int y_botom = 665;
	int center_random = 380;

	int random = rand() % 6;
	if (random <= 1)
		center_random = y_center - 175;
	else if (random <= 3)
		center_random = y_center;
	else if (random <= 5)
		center_random = y_center + 175;

	switch (enemy_random)
	{
	case 0:
		break;
	case 1:	//ジグザグ
		if (pattern_timer >= 1.0f)
		{
			pattern_timer = 0.0f;
			object_manager->CreateGameObject<Enemy1>(Vector2D(1300, center_random));
		}
		break;
	case 2:	//大砲
		if (pattern_timer >= 1.3)
		{
			pattern_timer = 0.0f;
			if (random <= 2)
				object_manager->CreateGameObject<Enemy2>(Vector2D(1300, y_top))->SetTrans();
			else if (random <= 5)
				object_manager->CreateGameObject<Enemy2>(Vector2D(1300, y_botom));
			
		}
		break;
	case 3:	//特攻
		if (pattern_timer >= 1.6)
		{
			pattern_timer = 0.0f;
			object_manager->CreateGameObject<Enemy3>(Vector2D(1300, center_random));
		}
		break;
	default:
		break;
	}
}

//雑魚生成2
void InGameScene::Spawn2()
{
	int y_top = 95;
	int y_center = 380;
	int y_botom = 665;

	int y_random = (150 * enemy_random_y) + 5;

	switch (enemy_random)
	{
	case 0:
		break;
	case 1:	//Z軌道
		if (pattern_timer >= 0.6f)
		{
			pattern_timer = 0.0f;
			object_manager->CreateGameObject<Enemy4>(Vector2D(1300, y_random));
		}
		break;
	case 2:	//自機狙い
		if (pattern_timer >= 2.0f)
		{
			pattern_timer = 0.0f;
			object_manager->CreateGameObject<Enemy5>(Vector2D(1300, y_random));

		}
		break;
	case 3:
		if (pattern_timer >= 1.6)
		{
			pattern_timer = 0.0f;
			object_manager->CreateGameObject<Enemy6>(Vector2D(1300, y_random));
		}
		break;
	default:
		break;
	}
}

//雑魚生成3
void InGameScene::Spawn3()
{
	int y_top = 95;
	int y_center = 380;
	int y_botom = 665;

	int y_random = (150 * enemy_random_y) + 5;

	switch (enemy_random)
	{
	case 0:
		break;
	case 1:	//
	case 2:	//
		if (pattern_timer >= 1.0f)
		{
			pattern_timer = 0.0f;
			object_manager->CreateGameObject<Enemy7>(Vector2D(1300, y_random));
		}
		break;
	case 3:	//
	case 4:	//
		if (pattern_timer >= 2.0f)
		{
			pattern_timer = 0.0f;
			object_manager->CreateGameObject<Enemy8>(Vector2D(1300, y_random));
		}
		break;
	case 5:	//
		if (pattern_timer >= 3.0f)
		{
			pattern_timer = 0.0f;
			object_manager->CreateGameObject<Enemy9>(Vector2D(1300, y_center));
		}
		break;
	default:
		break;
	}
}

//ボス生成管理処理
void InGameScene::BossManager()
{
	if (stage_level == 1)
	{
		//ボスの生成
		if (boss_flag == false)
		{
			boss_flag = true;
			boss1 = object_manager->CreateGameObject<Boss1>(Vector2D(1400, 400));
		}
		//ボス削除
		if (boss1->GetDeathFlag())
		{
			boss_flag = false;
			stage_level += 1;
			time_count = 60.0f;
			object_manager->DestroyGameObject(boss1);
			// score->SetStageLevel(stage_level);
		}

		//ボス死亡時画面内に残ったものを爆発
		if (boss1->GetBoss1Hp() <= 0)
		{
			for (GameObject* obj : scene_objects_list)
			{
				eObjectType type = obj->GetCollision().object_type;
				if (obj != boss1 && type == eEnemy || type == eEnemyShot)
				{
					obj->KeepDeathLocation();
				}
			}
		}
		else
		{
			for (GameObject* obj : scene_objects_list)
			{
				obj->SetDeathLocation();
			}
		}
	}
	else if (stage_level == 2)
	{
		//ボスの生成
		if (boss_flag == false)
		{
			boss_flag = true;
			boss2 = object_manager->CreateGameObject<Boss2>(Vector2D(1400, 400));
		}
		//ボス削除
		if (boss2->GetDeathFlag())
		{
			boss_flag = false;
			stage_level += 1;
			time_count = 60.0f;
			object_manager->DestroyGameObject(boss2);
		}
		//ボス死亡時画面内に残ったものを爆発
		if (boss2->GetBoss2Hp() <= 0)
		{
			for (GameObject* obj : scene_objects_list)
			{
				eObjectType type = obj->GetCollision().object_type;
				if (obj != boss2 && type == eEnemy || type == eEnemyShot)
				{
					obj->KeepDeathLocation();
				}
			}
		}
		else
		{
			for (GameObject* obj : scene_objects_list)
			{
				obj->SetDeathLocation();
			}
		}
	}
	else if (stage_level == 3)
	{
		//ボスの生成
		if (boss_flag == false)
		{
			boss_flag = true;
			boss3 = object_manager->CreateGameObject<Boss3>(Vector2D(1400, 400));
		}
		//ボス削除
		if (boss3->GetDeathFlag())
		{
			boss_flag = false;
			stage_level += 1;
			time_count = 60.0f;
			object_manager->DestroyGameObject(boss3);
		}
		//ボス死亡時画面内に残ったものを爆発
		if (boss3->GetBoss3Hp() <= 0)
		{
			for (GameObject* obj : scene_objects_list)
			{
				eObjectType type = obj->GetCollision().object_type;
				if (obj != boss3 && type == eEnemy || type == eEnemyShot)
				{
					obj->KeepDeathLocation();
				}
			}
		}
		else
		{
			for (GameObject* obj : scene_objects_list)
			{
				obj->SetDeathLocation();
			}
		}
	}

	//ボス撃破後画面暗転
	if (time_count <= 0.0f && boss_flag == true && dark_alpha < 255)
	{
		if (stage_level == 1 && boss1 != nullptr && 
			boss1->GetBoss1Hp() <= 0 && boss1->GetBoss1DeathCount() < 4.0f)
		{
			dark_alpha++;
		}
		if (stage_level == 2 && boss1 != nullptr &&
			boss2->GetBoss2Hp() <= 0 && boss2->GetBoss2DeathCount() < 4.0f)
		{
			dark_alpha++;
		}
		if (stage_level == 3 && boss3 != nullptr &&
			boss3->GetBoss3Hp() <= 0 && boss3->GetBoss3DeathCount() < 4.0f)
		{
			dark_alpha++;
		}
	}

	score->SetStageLevel(stage_level);
}