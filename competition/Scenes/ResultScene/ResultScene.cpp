#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
//#define DEBUG 1

ResultScene::ResultScene() : 
	m_selectedbutton(selectedbutton::Title), //初期はタイトル選択
	menu_num(0), 
	is_button(true), 
	back_ground_sound(0), 
	score(0), 
	back_ground_image(), 
	ranking(), 
	font(), 		
	window(),
	power_icon(),
	level(0),
	stagelevel(0),
	power(0),
	speed(0),
	cool_time(0),
	hit_range(0),
	three_way(false),
	drone(false),
	is_drone(false),
	is_max(false),
	is_check(false),
	color(0),
	button_location(),
	circle(0),
	is_cir(false),
	is_flash(true),
	flash_timer(0.0f),
	is_flg(false)
{
	// //リソース管理インスタンス取得
	// ResourceManager* rm = ResourceManager::GetInstance();
	// 
	// //画像取得
	
	sounds_effect[0] = NULL;
	sounds_effect[1] = NULL;
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);

	//画像取得
	back_ground_image = rm->GetImages("Resource/Images/back_ground/universe_asteroid03.png")[0];		// 背景画像
	// 音源取得
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM/Title/Title.mp3");

	// ボタン決定音
	sounds_effect[0] = rm->GetSounds("Resource/Sounds/SoundsEffect/Button/button_enter.mp3");
	// 選択音
	sounds_effect[1] = rm->GetSounds("Resource/Sounds/SoundsEffect/Button/button_select.mp3");
	// ボタン決定音の音量の設定
	ChangeVolumeSoundMem(200, sounds_effect[0]);
	// 選択音の音量の設定
	ChangeVolumeSoundMem(200, sounds_effect[1]);
	//選択状態リセット
	m_selectedbutton = selectedbutton::Title;

	// 音源再生
	ChangeVolumeSoundMem(100, back_ground_sound);
	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK, TRUE);

	// ranking = new RankingScene();
	// ranking->Initialize();

	// フォントの登録
	// font_name.push_back(CreateFontToHandle("魔導太丸ゴシック", 70, 6));
	// font_name.push_back(CreateFontToHandle("魔導太丸ゴシック", 40, 6));
	// font_name.push_back(CreateFontToHandle("魔導太丸ゴシック", 50, 6));
	// font_name.push_back(CreateFontToHandle("魔導太丸ゴシック", 100, 6));
	// font_name.push_back(CreateFontToHandle("魔導太丸ゴシック", 80, 6));

	font[0] = CreateFontToHandle("魔導太丸ゴシック", 40, 6);
	font[1] = CreateFontToHandle("魔導太丸ゴシック", 50, 6);
	font[2] = CreateFontToHandle("魔導太丸ゴシック", 70, 6);
	font[3] = CreateFontToHandle("魔導太丸ゴシック", 80, 6);
	font[4] = CreateFontToHandle("魔導太丸ゴシック", 100, 6);

	// power_icon[0] = rm->GetImages("Resource/Images/UpGrade_Icon/hp.png")[0];
	power_icon[0] = rm->GetImages("Resource/Images/UpGrade_Icon/power.png")[0];
	power_icon[1] = rm->GetImages("Resource/Images/UpGrade_Icon/speed.png")[0];
	power_icon[2] = rm->GetImages("Resource/Images/UpGrade_Icon/shot_speed.png")[0];
	power_icon[3] = rm->GetImages("Resource/Images/UpGrade_Icon/shot_size.png")[0];
	power_icon[4] = rm->GetImages("Resource/Images/UpGrade_Icon/three_way.png")[0];
	power_icon[5] = rm->GetImages("Resource/Images/UpGrade_Icon/drone.png")[0];

	window = rm->GetImages("Resource/Images/LevelUpUi/Table_01.png")[0];

	stagelevel = (score->GetStageLevel() * 100) / MAX_STAGE;
	level = score->GetPlayerLevel();

	// プレイヤーが取った強化内容を確認する
	// power = (score->GetPlayerPower() - 1);				
	power = score->GetPlayerPower();
	// speed = ((score->GetPlayerSpeed() / 5) - 19);			
	speed = score->GetPlayerSpeed();
	cool_time = score->GetPlayerCoolTime();			
	hit_range = score->GetPlayerHitRange();			
	three_way = score->GetPlayerThreeWay();				
	drone = score->GetPlayerDrone();

	is_check = true;

	button_location = Vector2D((D_WIN_MAX_X / 4), 630);

}

eSceneType ResultScene::Update(const float& delta_second)
{
	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	if (is_check == true)
	{
		CheckData();
	}

	// 点滅用タイマー処理（5秒ごとに表示/非表示を切り替え）
	flash_timer += delta_second;
	if (flash_timer >= 0.3f)
	{
		if (is_flash == true)				// 表示/非表示の切り替え
		{
			is_flash = false;
		}
		else
		{
			is_flash = true;
		}
		flash_timer = 0.0f;       // タイマーをリセット
	}


	///*プレイヤーの情報がマイナスをいった時、値を0にする*/
	//if (speed < 0)
	//{
	//	speed = 0;
	//}

	//if (power < 0)
	//{
	//	power = 0;
	//}

	///*ドローンが取得されたか*/
	//if (drone > 0)
	//{
	//	is_drone = true;
	//}
	//else
	//{
	//	is_drone = false;
	//}

	///*プレイヤーの弾のクールタイムが上限に行かないようにする*/
	//if (cool_time < 11)
	//{
	//	is_max = true;
	//}
	//else
	//{
	//	is_max = false;
	//}

	//// 全体の進捗度で色を変える
	//switch (stagelevel)
	//{
	//case 25:
	//	color = 1;
	//	break;
	//case 50:
	//	color = 2;
	//	break;
	//case 75:
	//	color = 3;
	//	break;
	//case 100:
	//	color = 4;
	//	break;
	//default:
	//	color = 0;
	//	break;
	//}


	//入力情報の更新
	input->Update();

	// カーソル右移動
	if (input->GetKeyUp(KEY_INPUT_D) || input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT) && is_button == true)
	{
		PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

		menu_num--;
		if (menu_num < 0)
		{
			menu_num = 1;
		}
	}

	// カーソル左移動
	if (input->GetKeyUp(KEY_INPUT_A) || input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT) && is_button == true)
	{
		PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

		menu_num++;
		if (menu_num > 1)
		{
			menu_num = 0;
		}
	}


	if (input->GetKeyUp(KEY_INPUT_E) || input->GetButtonDown(XINPUT_BUTTON_A) && is_button == true)
	{
		switch (menu_num)
		{
		case 0:
			//タイトルシーンへ遷移
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_NORMAL, TRUE);
			return eSceneType::eTitle;
			break;
		case 1:
			//ゲームを終了			// リスタートにする
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_NORMAL, TRUE);
			return eSceneType::eInGame;
			break;
		default:
			break;

		}
	}

	if (menu_num == 0)
	{
		is_cir = true;
		Cursor();
	}
	else
	{
		is_cir = false;
		Cursor();
	}

	
	return GetNowSceneType();
}

void ResultScene::Draw() const
{
#ifdef DEBUG
	/*		リザルト画面案*/
// ランク
	DrawBox(50, 20, 615, 550, 0xffffff, TRUE);
	DrawFormatString(50, 270, 0x000000, "スコアランク");

	// スコア結果
	DrawBox(665, 20, 1230, 550, 0xffffff, TRUE);
	DrawFormatString(665, 270, 0x000000, "スコア結果");


	DrawFormatString(250, 500, 0x00ffff, "到達したステージ: %d", stagelevel);		// 到達したレベルを描画する
	DrawFormatString(250, 600, 0x00ffff, "現在のレベル: %d", level);		// 現在のレベルを描画する

#endif // DEBUG

	char buf[256];

	// 背景画像
	DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);

	//DrawBox(50, 20, 1230, 550, 0xffffff, TRUE);
	// DrawFormatString(50, 20, 0xffffff, "Result");
	// DrawStringToHandle(50, 20, "RESULT", GetColor(255, 255, 255), font_name[2]);
	DrawStringToHandle(50, 20, "RESULT", GetColor(255, 255, 255), font[1]);


	// DrawFormatString(50, 80, 0xffffff, "到達したステージ");
	// DrawStringToHandle(50, 80, "到達したステージ", GetColor(255, 255, 255), font_name[2]);
	DrawStringToHandle(50, 80, "到達度", GetColor(255, 255, 255), font[1]);

	snprintf(buf, sizeof(buf), "%d％", stagelevel);
	// DrawFormatString(1200, 80, 0xffffff, "%d", stagelevel);		// 到達したレベルを描画する
	// DrawStringToHandle(1200, 80, buf, GetColor(255, 255, 255), font_name[2]);

	switch (color)
	{
	case 1:
		DrawStringToHandle(550, 80, buf, GetColor(0, 0, 255), font[1]);
		break;
	case 2:
		DrawStringToHandle(550, 80, buf, GetColor(0, 255, 0), font[1]);
		break;
	case 3:
		DrawStringToHandle(550, 80, buf, GetColor(255, 255, 0), font[1]);
		break;
	case 4:
		DrawStringToHandle(550, 80, buf, GetColor(255, 0, 255), font[1]);
		break;
	default:
		DrawStringToHandle(550, 80, buf, GetColor(255, 0, 0), font[1]);
		break;
	}

	// DrawStringToHandle(550, 80, buf, GetColor(255, 255, 255), font[1]);

	// DrawFormatString(50, 140, 0xffffff, "現在のレベル");
	// DrawStringToHandle(50, 140, "現在のレベル", GetColor(255, 255, 255), font_name[2]);
	DrawStringToHandle(50, 140, "到達レベル", GetColor(255, 255, 255), font[1]);

	snprintf(buf, sizeof(buf), "%d", level);
	// DrawFormatString(1200, 140, 0xffffff, "%d", level);		// プレイヤーの現在の死亡時のレベルを描画する
	// DrawStringToHandle(1200, 140, buf, GetColor(255, 255, 255), font_name[2]);
	DrawStringToHandle(550, 140, buf, GetColor(255, 255, 255), font[1]);


	// 強化した内容を描画する
	DrawStringToHandle(50, 200, "アップグレードした内容", GetColor(255, 255, 255), font[1]);
	
	
	// 外枠の描画
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraphF(125 + (i * 200), 450, 0.5, 0, window, TRUE);
	}
	
	// アイコンの描画
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraphF(125 + (i * 200), 400, 0.5, 0, power_icon[i], TRUE);
	}
	
	// 強化した値を設定する描画
	/*パワー*/
	snprintf(buf, sizeof(buf), "Lv %d", power);
	DrawStringToHandle(75, 500, buf, GetColor(255, 255, 255), font[1]);
	/*プレイヤーのスピード*/
	snprintf(buf, sizeof(buf), "Lv %d", speed);
	if (is_flg == true)
	{
		DrawStringToHandle(255, 500, "Lv MAX", GetColor(255, 255, 255), font[1]);
	}
	else
	{
		DrawStringToHandle(275, 500, buf, GetColor(255, 255, 255), font[1]);
	}
	/*プレイヤーの弾のスピード(クールタイム)*/
	snprintf(buf, sizeof(buf), "Lv %d", cool_time);
	if (is_max != true)
	{
		DrawStringToHandle(455, 500, "Lv MAX", GetColor(255, 255, 255), font[1]);
	}
	else
	{
		DrawStringToHandle(475, 500, buf, GetColor(255, 255, 255), font[1]);
	}
	/*プレイヤーの弾の当たり判定*/
	snprintf(buf, sizeof(buf), "Lv %d", hit_range);
	DrawStringToHandle(675, 500, buf, GetColor(255, 255, 255), font[1]);
	/*3ウェイ弾を取得したか*/
	if (three_way == true)
	{
		DrawStringToHandle(855, 500, "Lv MAX", GetColor(255, 255, 255), font[1]);
	}
	else
	{
		DrawStringToHandle(875, 500, "Lv 0", GetColor(255, 255, 255), font[1]);
	}
	/*ドローンを取得したかどうか*/		// 取得した数だからドローンが破壊されても1カウントされている
	if (is_drone == true)
	{
		// snprintf(buf, sizeof(buf), "LvMAX", drone);
		// DrawStringToHandle(1090, 500, buf, GetColor(255, 255, 255), font[1]);
		DrawStringToHandle(1055, 500, "Lv MAX", GetColor(255, 255, 255), font[1]);
	}
	else
	{
		DrawStringToHandle(1075, 500, "Lv 0", GetColor(255, 255, 255), font[1]);
	}

	// エンドボタン
	int endColor = (m_selectedbutton == selectedbutton::Title) ? GetColor(255, 0, 0) : GetColor(128, 128, 128);
	//DrawBox(25, 600, 325, 700, 0xffffff, TRUE);
	// DrawFormatString(25, 630, endColor, "Title");		// タイトルボタンに変更
	// DrawStringToHandle(25, 630, "Title", GetColor(255, 0, 0), font_name[2]);
	// DrawStringToHandle(25, 630, "Title", GetColor(255, 0, 0), font[1]);
	// DrawStringToHandle(button_location.x, button_location.y, "Title", GetColor(255, 0, 0), font[1]);

	// タイトルボタン
	int titleColor = (m_selectedbutton == selectedbutton::End) ? GetColor(255, 0, 0) : GetColor(255, 255, 255);
	//DrawBox(955, 600, 1255, 700, 0xffffff, TRUE);
	// DrawFormatString(955, 630, titleColor, "End");		// エンドボタンに変更
	// DrawStringToHandle(955, 630, "End", GetColor(255, 255, 255), font_name[2]);
	// DrawStringToHandle(955, 630, "End", GetColor(255, 255, 255), font[1]);
	// DrawStringToHandle((button_location.x * 3), button_location.y, "End", GetColor(255, 255, 255), font[1]);


		switch (menu_num)
		{
		case 0:
			DrawStringToHandle(button_location.x, button_location.y, "TITLE", GetColor(255, 0, 0), font[1]);
			DrawStringToHandle((button_location.x * 3), button_location.y, "RESTART", GetColor(255, 255, 255), font[1]);
			// DrawTriangle(5, 640, 5, 660, 25, 650, GetColor(255, 0, 0), TRUE);
			if (is_flash == true)
			{
				DrawCircle(circle, 650, 10, GetColor(255, 0, 0), TRUE);
			}
			else
			{
				// DrawTriangle(tri1, 640, tri2, 660, tri3, 650, GetColor(255, 0, 0), FALSE); // 枠だけ
				DrawCircle(circle, 650, 10, GetColor(200, 0, 0), TRUE);
			}
			break;
		case 1:
			DrawStringToHandle(button_location.x, button_location.y, "TITLE", GetColor(255, 255, 255), font[1]);
			DrawStringToHandle((button_location.x * 3), button_location.y, "RESTART", GetColor(255, 0, 0), font[1]);
			// DrawTriangle(935, 640, 935, 660, 955, 650, GetColor(255, 0, 0), TRUE);
			if (is_flash == true)
			{
				// DrawTriangle(tri1, 640, tri2, 660, tri3, 650, GetColor(255, 0, 0), TRUE);  // 塗りつぶし
				DrawCircle(circle, 650, 10, GetColor(255, 0, 0), TRUE);
			}
			else
			{
				// DrawTriangle(tri1, 640, tri2, 660, tri3, 650, GetColor(255, 0, 0), FALSE);  // 塗りつぶし
				DrawCircle(circle, 650, 10, GetColor(200, 0, 0), TRUE);
			}
			break;
		default:
			break;
		}
}

void ResultScene::Finalize()
{
	// ranking->SetRank(stagelevel);
	
	//StopSoundMem()

	// 設定したフォントを削除する
	for (int i = 0; i < 5; i++)
	{
		DeleteFontToHandle(font[i]);
	}


	StopSoundMem(back_ground_sound);
	score->Finalize();

	is_check = false;
}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}

void ResultScene::CheckData()
{
	/*プレイヤーの情報がマイナスをいった時、値を0にする*/
	if (speed > 5)
	{
		is_flg = true;
	}

	if (power < 0)
	{
		power = 0;
	}

	/*ドローンが取得されたか*/
	if (drone > 0)
	{
		is_drone = true;
	}
	else
	{
		is_drone = false;
	}

	/*プレイヤーの弾のクールタイムが上限に行かないようにする*/
	if (cool_time < 10)
	{
		is_max = true;
	}
	else
	{
		is_max = false;
	}

	// 全体の進捗度で色を変える
	switch (stagelevel)
	{
	case 25:
		color = 1;
		break;
	case 50:
		color = 2;
		break;
	case 75:
		color = 3;
		break;
	case 100:
		color = 4;
		break;
	default:
		color = 0;
		break;
	}


}

void ResultScene::Cursor()
{
	if (is_cir == true)
	{
		circle = ((D_WIN_MAX_X / 4) - 20);
	}
	else
	{
		circle = (((D_WIN_MAX_X / 4) * 3) - 20);

	}
}

