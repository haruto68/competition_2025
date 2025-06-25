#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

TitleScene::TitleScene() : menu_num(0), help(false), is_button(true), back_ground_sound(NULL), back_ground_image(), font{}
{
	//リソース管理インスタンス取得
	// ResourceManager* rm = ResourceManager::GetInstance();

	// 画像取得
	// 音源取得
	// back_ground_sound = rm->GetSounds("Resource/Sounds/BGM/Title/Title.mp3");
	sounds_effect[0] = NULL;
	sounds_effect[1] = NULL;

	back_ground_location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// UI画像の格納
	ui_button.push_back(rm->GetImages("Resource/Images/Buttons/steamcontroller/steam_dpad.png")[0]);
	ui_button.push_back(rm->GetImages("Resource/Images/Buttons/steamcontroller/steam_button_color_a.png")[0]);
	ui_button.push_back(rm->GetImages("Resource/Images/Buttons/steamcontroller/steam_button_color_b.png")[0]);

	// 画像の位置座標の設定
	ui_location.push_back(Vector2D(32, D_WIN_MAX_Y - 32));
	ui_location.push_back(Vector2D(((D_WIN_MAX_X / 2) + 200), D_WIN_MAX_Y - 32));

	// フォントの座標の設定
	font_location.push_back(Vector2D(64, D_WIN_MAX_Y - 50));
	font_location.push_back(Vector2D(904, D_WIN_MAX_Y - 50));


	// 画像取得
	back_ground_image = rm->GetImages("Resource/Images/back_ground/universe_asteroid03.png")[0];		// 背景画像
	// 音源取得
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM/Title/Title.mp3");
	// ボタン決定音
	sounds_effect[0] = rm->GetSounds("Resource/Sounds/SoundsEffect/Button/button_enter.mp3");
	// 選択音
	sounds_effect[1] = rm->GetSounds("Resource/Sounds/SoundsEffect/Button/button_select.mp3");
	// 音源の音量の設定
	ChangeVolumeSoundMem(100, back_ground_sound);
	// ボタン決定音の音量の設定
	ChangeVolumeSoundMem(200, sounds_effect[0]);
	// 選択音の音量の設定
	ChangeVolumeSoundMem(200, sounds_effect[1]);
	// 音源の再生
	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_LOOP, TRUE);
	
	// フォントを設定する
	// title_name = CreateFontToHandle("魔導太丸ゴシック", 150, 6);
	// button = CreateFontToHandle("魔導太丸ゴシック", 40, 6);
	// push_button = CreateFontToHandle("魔導太丸ゴシック", 60, 6);

	// ヘルプ画面のフォントの設定
	// help_font = CreateFontToHandle("魔導太丸ゴシック", 50, 6);
	// help_font_title = CreateFontToHandle("魔導太丸ゴシック", 70, 6);

	// フォントの設定
	font[0] = CreateFontToHandle("魔導太丸ゴシック", 40, 6);
	font[1] = CreateFontToHandle("魔導太丸ゴシック", 50, 6);
	font[2] = CreateFontToHandle("魔導太丸ゴシック", 60, 6);
	font[3] = CreateFontToHandle("魔導太丸ゴシック", 70, 6);
	font[4] = CreateFontToHandle("魔導太丸ゴシック", 150, 6);


	//音源取得(0: 敵が破壊時の音 1: 敵が弾を撃った時の音)
	rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemybreak.mp3");
	rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemyshot.mp3");
}

eSceneType TitleScene::Update(const float& delta_second)
{
	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//入力情報の更新
	input->Update();

	//ゲームを終了
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	// ヘルプが開かれていると操作を停止する
	if (help != true)
	{
		// カーソル上移動
		if ((input->GetButtonDown(XINPUT_BUTTON_DPAD_UP) || input->GetKeyDown(KEY_INPUT_W)) && is_button == true)
		{
			PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

			menu_num--;
			if (menu_num < 0)
			{
				menu_num = 2;
			}
		}

		// カーソル下移動
		if ((input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || input->GetKeyDown(KEY_INPUT_S)) && is_button == true)
		{
			PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

			menu_num++;
			if (menu_num > 2)
			{
				menu_num = 0;
			}
		}

	}

	// カーソル決定(決定した画面に移動する)
	if ((input->GetButtonDown(XINPUT_BUTTON_A) || (input->GetKeyDown(KEY_INPUT_E) || input->GetKeyDown(KEY_INPUT_1))) && is_button == true)
	{
		switch (menu_num)
		{
		case 0:
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_BACK, TRUE);
			return eSceneType::eInGame;
		case 1:
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_BACK, TRUE);
			if (help)
				help = false;
			else
				help = true;
			break;
		case 2:
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_NORMAL, TRUE);
			return eSceneType::eExit;
		}
	}

	if (input->GetButtonDown(XINPUT_BUTTON_B) || input->GetKeyDown(KEY_INPUT_2))
	{
		PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_BACK, TRUE);
		help = false;
		is_button = true;
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	// 背景画像
	DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);

	// int font[3] = { 40,40,40 };
	// font[menu_num] = 60;

	// タイトルの大見出し
	// DrawBox(50, 20, 1230, 420, 0xffffff, TRUE);
	// SetFontSize(150);

	// DrawFormatString(100, 175, 0xffffff, "Nebula striker");

	/*シーン選択*/
	// Startボタン(ゲームメインに遷移する)
	// DrawBox(480, 435, 800, 510, 0xffffff, TRUE);
	// SetFontSize(font[0]);
	// DrawFormatString(480, 450, 0xffffff, "Game Start");

	// Helpボタン(ヘルプ画面に遷移する)
	// DrawBox(480, 525, 800, 600, 0xffffff, TRUE);
	// SetFontSize(font[1]);
	// DrawFormatString(480, 540, 0xffffff, "Help");

	// Rankingボタン(ランキング画面に遷移する)
	// DrawBox(480, 615, 800, 690, 0xffffff, TRUE);
	// SetFontSize(font[2]);
	// DrawFormatString(480, 630, 0xffffff, "Ranking");

	// SetFontSize(40);
	// DrawFormatString(65, 450, GetColor(255, 255, 255), "十字ボタン");
	// DrawFormatString(65, 500, GetColor(255, 255, 255), "      カーソル移動");
	// DrawFormatString(65, 580, GetColor(0, 255, 0), "A　決定");
	
	// タイトルの描画
	// DrawStringToHandle(100, 175, "Nebula Striker", GetColor(255, 0, 255), title_name);
	DrawStringToHandle(100, 175, "Nebula Striker", GetColor(255, 0, 255), font[4]);

	// 十字キーでカーソル移動
	DrawRotaGraphF(ui_location[0].x, ui_location[0].y, 0.5, 0.0, ui_button[0], TRUE);
	// DrawStringToHandle(font_location[0].x, font_location[0].y, "カーソル移動", GetColor(255, 0, 255), button);
	DrawStringToHandle(font_location[0].x, font_location[0].y, "カーソル移動", GetColor(255, 0, 255), font[0]);

	// Aボタンで決定
	DrawRotaGraphF(ui_location[1].x, ui_location[1].y, 0.5, 0.0, ui_button[1], TRUE);
	// DrawStringToHandle(font_location[1].x, font_location[1].y, "決定", GetColor(255, 0, 255), button);
	DrawStringToHandle(font_location[1].x, font_location[1].y, "決定", GetColor(255, 0, 255), font[0]);

	// 仮カーソルUI	
	switch (menu_num)
	{
		case 0:
			DrawCircle(465, 473, 7, 0xff0000, TRUE);
			DrawStringToHandle(480, 450, "Game Start", GetColor(255, 0, 0), font[2]);
			DrawStringToHandle(480, 540, "Help", GetColor(255, 0, 255), font[0]);
			DrawStringToHandle(480, 630, "End", GetColor(255, 0, 255), font[0]);
			break;
		case 1:
			DrawCircle(465, 563, 7, 0xff0000, TRUE);
			DrawStringToHandle(480, 450, "Game Start", GetColor(255, 0, 255), font[0]);
			DrawStringToHandle(480, 540, "Help", GetColor(255, 0, 0), font[2]);
			DrawStringToHandle(480, 630, "End", GetColor(255, 0, 255), font[0]);
			break;
		case 2:
			DrawCircle(465, 653, 7, 0xff0000, TRUE);
			DrawStringToHandle(480, 450, "Game Start", GetColor(255, 0, 255), font[0]);
			DrawStringToHandle(480, 540, "Help", GetColor(255, 0, 255), font[0]);
			DrawStringToHandle(480, 630, "End", GetColor(255, 0, 0), font[2]);
			break;
		default:
			break;
	}

	if (help)
	{
		// SetFontSize(50);
		DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);
		// DrawFormatString(0, 0, 0xffffff, "HELP");
		// DrawFormatString(0, 200, 0xffffff, "・左スティックで移動");
		// DrawFormatString(0, 300, 0xffffff, "・Bボタンで弾の発射");
		// DrawFormatString(0, 400, 0xffffff, "・Yボタンでアップグレード");
		// DrawFormatString(0, 500, 0x000000, "Bボタンでタイトルに戻る");
		SetFontSize(40);
		
		// test
		DrawStringToHandle(10, 10, "HELP", GetColor(255, 0, 255), font[3]);
		DrawStringToHandle(10, 210, "左スティック移動", GetColor(255, 0, 255), font[1]);
		DrawStringToHandle(10, 310, "Bボタンで弾の発射", GetColor(255, 0, 255), font[1]);
		DrawStringToHandle(10, 410, "Yボタンでアップグレード", GetColor(255, 0, 255), font[1]);
		DrawRotaGraphF(870, 685, 0.5, 0.0, ui_button[2], TRUE);
		DrawStringToHandle(900, 660, "タイトルに戻る", 0xff00ff, font[1]);
		// DrawStringToHandle(0, 400, "HELP", 0xfff00ff, help_font);
	}
}

void TitleScene::Finalize()
{
	// BGMの再生を止める
	StopSoundMem(back_ground_sound);

	// 設定したフォントを削除する
	for (int i = 0; i < 5; i++)
	{
		DeleteFontToHandle(font[i]);
	}
}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}