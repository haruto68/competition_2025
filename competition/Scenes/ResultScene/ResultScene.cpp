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
		/*		リザルト画面案*/
		// ランク
		DrawBox(50, 20, 615, 550, 0xffffff, TRUE);
		DrawFormatString(50, 270, 0x000000, "スコアランク");

		// スコア結果
		DrawBox(665, 20, 1230, 550, 0xffffff, TRUE);
		DrawFormatString(665, 270, 0x000000, "スコア結果");

		// エンドボタン
		DrawBox(25, 600, 325, 700, 0xffffff, TRUE);
		DrawFormatString(25, 630, 0xff0000, "End");

		// ネクストぼタン
		DrawBox(955, 600, 1255, 700, 0xffffff, TRUE);
		DrawFormatString(955, 630, 0x0000ff, "Next");
	
}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}