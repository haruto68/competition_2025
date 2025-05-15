#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"

TitleScene::TitleScene() : menu_num(0), help(false), is_button(true)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	//画像取得
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{

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

	// カーソル上移動
	if ((input->GetKeyDown(KEY_INPUT_W) ||
		input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))
		&& !help)
	{
		menu_num--;
		if (menu_num < 0)
		{
			menu_num = 2;
		}
	}

	// カーソル下移動
	if ((input->GetKeyDown(KEY_INPUT_S) ||
		input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
		&& !help)
	{
		menu_num++;
		if (menu_num > 2)
		{
			menu_num = 0;
		}
	}

	// カーソル決定(決定した画面に移動する)
	if (input->GetKeyDown(KEY_INPUT_E) ||
		input->GetButtonDown(XINPUT_BUTTON_A))
	{
		switch (menu_num)
		{
		case 0:
			return eSceneType::eInGame;
		case 1:
			if (help)
				help = false;
			else
				help = true;
			break;
		case 2:
			return eSceneType::eRanking;
		}
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	int font[3] = { 40,40,40 };
	font[menu_num] = 60;

	// タイトルの大見出し
	DrawBox(50, 20, 1230, 420, 0xffffff, TRUE);
	SetFontSize(40);
	DrawFormatString(50, 175, 0x000000, "ゲームの名前(仮)");

	/*シーン選択*/
	// Startボタン(ゲームメインに遷移する)
	DrawBox(480, 435, 800, 510, 0xffffff, TRUE);
	SetFontSize(font[0]);
	DrawFormatString(480, 450, 0x000000, "Game Start");

	// Helpボタン(ヘルプ画面に遷移する)
	DrawBox(480, 525, 800, 600, 0xffffff, TRUE);
	SetFontSize(font[1]);
	DrawFormatString(480, 540, 0x000000, "Help");

	// Rankingボタン(ランキング画面に遷移する)
	DrawBox(480, 615, 800, 690, 0xffffff, TRUE);
	SetFontSize(font[2]);
	DrawFormatString(480, 630, 0x000000, "Ranking");

	SetFontSize(40);
	DrawFormatString(70, 450, GetColor(255, 255, 255), "十字ボタン");
	DrawFormatString(70, 500, GetColor(255, 255, 255), "      カーソル移動");
	DrawFormatString(70, 580, GetColor(0, 255, 0), "A　決定");

	// 仮カーソルUI	時間があれば治します。
	switch (menu_num)
	{
		case 0:
			DrawCircle(465, 473, 7, 0xff0000, TRUE);
			break;
		case 1:
			DrawCircle(465, 563, 7, 0xff0000, TRUE);
			break;
		case 2:
			DrawCircle(465, 653, 7, 0xff0000, TRUE);
			break;
		default:
			break;
	}

	if (help)
	{
		SetFontSize(50);
		DrawBox(0, 0, 1280, 720, GetColor(0,150,200), TRUE);
		DrawFormatString(0, 0, 0x000000, "一応ヘルプ");
		DrawFormatString(0, 200, 0x000000, "WASDキーで移動");
		DrawFormatString(0, 300, 0x000000, "Bボタンで弾の発射");
		SetFontSize(40);
		DrawFormatString(70, 580, GetColor(0, 255, 0), "A　戻る");
	}
}

void TitleScene::Finalize()
{

}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}