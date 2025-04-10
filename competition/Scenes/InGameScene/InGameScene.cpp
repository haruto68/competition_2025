#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"

InGameScene::InGameScene()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	//画像取得
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{

}

eSceneType InGameScene::Update(const float& delta_second)
{
	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//入力情報の更新
	input->Update();

	//インゲームシーンへ遷移
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
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
	DrawFormatString(10, 10, GetColor(255, 255, 255), "インゲームシーン");
}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}