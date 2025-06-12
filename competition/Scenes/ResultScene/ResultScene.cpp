#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
//#define DEBUG 1

ResultScene::ResultScene(): m_selectedbutton(selectedbutton::Title), menu_num(0), is_button(true), back_ground_sound(0), score(0)			//初期はタイトル選択
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

	//画像取得
	
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

	ranking = new RankingScene();
	// ranking->Initialize();
}

eSceneType ResultScene::Update(const float& delta_second)
{
	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	stagelevel = score->GetStageLevel();
	level = score->GetStageLevel();
	//入力情報の更新
	input->Update();

	// カーソル右移動
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT) && is_button == true)
	{
		PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

		menu_num--;
		if (menu_num < 0)
		{
			menu_num = 1;
		}
	}

	// カーソル左移動
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT) && is_button == true)
	{
		PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

		menu_num++;
		if (menu_num > 1)
		{
			menu_num = 0;
		}
	}


	if (input->GetButtonDown(XINPUT_BUTTON_A) && is_button == true)
	{
		switch (menu_num)
		{
		case 0:
			//タイトルシーンへ遷移
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_NORMAL, TRUE);
			return eSceneType::eTitle;
			break;
		case 1:
			//ゲームを終了
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_NORMAL, TRUE);
			return eSceneType::eExit;
			break;
		default:
			break;

		}
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

	DrawBox(50, 20, 1230, 550, 0xffffff, TRUE);
	DrawFormatString(50, 20, 0x000000, "Result");

	DrawFormatString(50, 80, 0x000000, "到達したステージ");		
	DrawFormatString(1200, 80, 0x000000, "%d", stagelevel);		// 到達したレベルを描画する

	DrawFormatString(50, 140, 0x000000, "現在のレベル");
	DrawFormatString(1200, 140, 0x000000, "%d", level);		// プレイヤーの現在の死亡時のレベルを描画する

	// エンドボタン
	int endColor = (m_selectedbutton == selectedbutton::Title) ? GetColor(255, 0, 0) : GetColor(128, 128, 128);
	DrawBox(25, 600, 325, 700, 0xffffff, TRUE);
	DrawFormatString(25, 630, endColor, "Title");		// タイトルボタンに変更

	// タイトルボタン
	int titleColor = (m_selectedbutton == selectedbutton::End) ? GetColor(255, 0, 0) : GetColor(128, 128, 128);
	DrawBox(955, 600, 1255, 700, 0xffffff, TRUE);
	DrawFormatString(955, 630, titleColor, "End");		// エンドボタンに変更


		switch (menu_num)
		{
		case 0:
			DrawTriangle(5, 640, 5, 660, 25, 650, GetColor(255, 0, 0), TRUE);
			break;
		case 1:
			DrawTriangle(935, 640, 935, 660, 955, 650, GetColor(255, 0, 0), TRUE);
			break;
		default:
			break;
		}
}

void ResultScene::Finalize()
{
	ranking->SetRank(stagelevel);
	//StopSoundMem()
	StopSoundMem(back_ground_sound);
	score->Finalize();
}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}