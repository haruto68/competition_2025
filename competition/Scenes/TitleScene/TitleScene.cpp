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
}

void TitleScene::Finalize()
{

}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}