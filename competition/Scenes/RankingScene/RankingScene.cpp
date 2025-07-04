#include "RankingScene.h"
#include "../../Utility/InputManager.h"
#include "../../Resource/ResourceManager.h"

RankingScene::RankingScene() : back_ground_sound(NULL), score{}, rank{}, font{}
{
	// //リソース管理インスタンス取得
	// ResourceManager* rm = ResourceManager::GetInstance();
	
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
	back_ground_image = rm->GetImages("Resource/Images/back_ground/universe_asteroid03.png")[0];		// 背景画像
	button_image.push_back(rm->GetImages("Resource/Images/Buttons/steamcontroller/steam_button_color_b.png")[0]);
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

	back_ground_location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);

	// フォントの登録
	// font.push_back(CreateFontToHandle("魔導太丸ゴシック", 70, 6));
	// font.push_back(CreateFontToHandle("魔導太丸ゴシック", 50, 6));

	font[0] = CreateFontToHandle("魔導太丸ゴシック", 70, 6);
	font[1] = CreateFontToHandle("魔導太丸ゴシック", 50, 6);

	// ランキングデータの読み込み
	FILE* fp = nullptr;

	// ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/data/ranking.txt", "r");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/ranking_data.txtが開けませんでした\n");
	}

	// 対象ファイルからよみこむ
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fscanf_s(fp, "%d %d",&rank[i],  & score[i]);
	}

	// ファイルクローズ
	fclose(fp);
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
	// 背景画像
	DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);

	// DrawFormatString(10, 10, GetColor(255, 255, 255), "RANKING");
	// DrawFormatString(10, 110, GetColor(255, 0, 0), "Bボタンでタイトルに戻る");

	DrawStringToHandle(10, 10, "RANKING", GetColor(255, 255, 255), font[0]);
	// DrawStringToHandle(10, 110, "Bボタンでタイトルに戻る", GetColor(255, 255, 255), font[0]);

	char buf[128];

	//順位の描画
	for (int i = 0; i < RANKING_DATA; ++i)
	{

		// DrawFormatString(80, 200 + i * 85, 0xffffff, "No.%d  到達したステージ数", i + 1);
		// DrawFormatString(1200, 200 + i * 85, 0xffffff, "%d", score[i]);
		snprintf(buf, sizeof(buf), "No.%d 到達したステージ数", i + 1);
		DrawStringToHandle(80, 90 + i * 200, buf, GetColor(255, 255, 255), font[1]);

		snprintf(buf, sizeof(buf), "%d", score[i]);
		DrawStringToHandle(1200, 90 + i * 200, buf, GetColor(255, 255, 255), font[1]);
	}
	DrawRotaGraphF(870, 685, 0.5, 0.0, button_image[0], TRUE);
	DrawStringToHandle(900, 660, "タイトルに戻る", 0xffffff, font[1]);

}

void RankingScene::Finalize()
{
	StopSoundMem(back_ground_sound);
	for (int i = 0; i < 2; i++)
	{
		DeleteFontToHandle(font[i]);
	}
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}

void RankingScene::SortData()
{

	for (int i = 0; i < RANKING_DATA - 1; i++)
	{
		for (int j = i + 1; j < RANKING_DATA; j++)
		{
			if (score[i] < score[j])
			{
				int tmp = score[i];
				score[i] = score[j];
				score[j] = tmp;
			}
		}
	}

	// 順位を整列させる
	for (int i = 0; i < RANKING_DATA; i++)
	{
		rank[i] = 1;
	}
	for (int i = 0; i < RANKING_DATA - 1; i++)
	{
		for (int j = i + 1; j < RANKING_DATA; j++)
		{
			if (score[i] > score[j])
			{
				rank[j]++;
			}
		}
	}


	// ランキングデータの読み込み
	FILE* fp = nullptr;

	// ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/data/ranking.txt", "w");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/data/ranking.txtが開けませんでした\n");
	}

	// 対象ファイルに書き込み
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fprintf(fp, "%d %d\n", rank[i], score[i]);
	}

	// ファイルクローズ
	fclose(fp);
}


void RankingScene::SetRank(int score)
{
	//3位から順位を設定する
	if (this->score[RANKING_DATA - 1] < score)
	{
		if (this->score[RANKING_DATA - 2] != score && this->score[RANKING_DATA - 3] != score)
		{
			this->score[RANKING_DATA - 1] = score;
			SortData();
		}
	}

}

