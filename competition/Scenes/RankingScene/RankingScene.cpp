#include "RankingScene.h"
#include "../../Utility/InputManager.h"
#include "../../Resource/ResourceManager.h"

RankingScene::RankingScene() : back_ground_sound(NULL)
{
	// //リソース管理インスタンス取得
	// ResourceManager* rm = ResourceManager::GetInstance();
	// 
	// // 画像取得

	sounds_effect[0] = NULL;
	sounds_effect[1] = NULL;
}

RankingScene::~RankingScene()
{

}

void RankingScene::Initialize()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 画像取得

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

}

eSceneType RankingScene::Update(const float& delta_second)
{
	// 入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	// 入力情報の更新
	input->Update();

	// ゲーム終了
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	// 2キーでタイトルに戻る
	if (input->GetButtonDown(XINPUT_BUTTON_B) || input->GetKeyUp(KEY_INPUT_2))
	{
		PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_BACK, TRUE);
		return eSceneType::eTitle;
	}

	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "ランキングシーン");
	DrawFormatString(10, 110, GetColor(255, 255, 255), "Bボタンでタイトルに戻る");

}

void RankingScene::Finalize()
{
	StopSoundMem(back_ground_sound);
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}
