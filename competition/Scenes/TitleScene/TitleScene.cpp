#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"

TitleScene::TitleScene()
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

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "タイトルシーン");
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

	// Rankingボタン(ランキング画面に遷移する)←これを作らなくてエンドにしても良き
	DrawBox(480, 615, 800, 690, 0xffffff, TRUE);		
	DrawFormatString(480, 630, 0x000000, "Ranking");

}

void TitleScene::Finalize()
{

}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}