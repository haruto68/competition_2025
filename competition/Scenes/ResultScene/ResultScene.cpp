#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"

ResultScene::ResultScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	//画像取得
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{

}

eSceneType ResultScene::Update(const float& delta_second)
{
	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//入力情報の更新
	input->Update();

	//インゲームシーンへ遷移
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eTitle;
	}

	//ゲームを終了
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	return GetNowSceneType();
}

void ResultScene::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "リザルトシーン");
}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}