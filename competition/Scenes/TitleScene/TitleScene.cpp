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

	//インゲームシーンへ遷移
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eInGame;
	}

	//ゲームを終了
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	// カーソル上移動
	if (input->GetKeyDown(KEY_INPUT_W) && is_button == true)
	{
		menu_num--;
		if (menu_num < 0)
		{
			menu_num = 2;
		}
	}

	// カーソル下移動
	if (input->GetKeyDown(KEY_INPUT_S) && is_button == true)
	{
		menu_num++;
		if (menu_num > 2)
		{
			menu_num = 0;
		}
	}

	// カーソル決定(決定した画面に移動する)
	if (input->GetKeyDown(KEY_INPUT_1) && is_button == true)
	{
		switch (menu_num)
		{
			case 0:
				return eSceneType::eInGame;
				break;
			case 1:
				// return eSceneType::eInGame;
				help = true;
				is_button = false;
				break;
			case 2:
				return eSceneType::eRanking;
				break;
		}
	}

	if (input->GetKeyDown(KEY_INPUT_2))
	{
		help = false;
		is_button = true;
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	// DrawFormatString(10, 10, GetColor(255, 255, 255), "タイトルシーン");
	// タイトルの大見出し
	DrawBox(50, 20, 1230, 420, 0xffffff, TRUE);
	DrawFormatString(50, 175, 0x000000, "ゲームの名前(仮)");

	/*シーン選択*/
	// Startボタン(ゲームメインに遷移する)
	DrawBox(480, 435, 800, 510, 0xffffff, TRUE);		
	DrawFormatString(480, 450, 0x000000, "Game Start");

	// Helpボタン(ヘルプ画面に遷移する)
	DrawBox(480, 525, 800, 600, 0xffffff, TRUE);		
	DrawFormatString(480, 540, 0x000000, "Help");

	// Rankingボタン(ランキング画面に遷移する)
	DrawBox(480, 615, 800, 690, 0xffffff, TRUE);		
	DrawFormatString(480, 630, 0x000000, "Ranking");

	DrawFormatString(900, 500, 0xFFFFFF, "シーンの番号 %d", menu_num);		// 仮

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

	if (menu_num == 1 && help == true)
	{
		DrawBox(0, 0, 1280, 720, 0xff00ff, TRUE);
		DrawFormatString(0, 100, 0x000000, "一応ヘルプシーン");
		DrawFormatString(0, 100, 0x000000, "操作説明及び敵やオブジェクトの詳細説明");
		DrawFormatString(0, 200, 0x000000, "WASDキーで移動");
		DrawFormatString(0, 300, 0x000000, "Bボタンで弾の発射");
	}
	// ボタン操作確認
	DrawFormatString(800, 600, 0xFFFFFF, "ボタン操作の番号 %d", is_button);
	DrawFormatString(900, 500, 0xFFFFFF, "シーンの番号 %d", menu_num);
}

void TitleScene::Finalize()
{

}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}