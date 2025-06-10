#include "RankingScene.h"
#include "../../Utility/InputManager.h"
#include "../../Resource/ResourceManager.h"

RankingScene::RankingScene() : back_ground_sound(NULL), score{}, rank{}
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
	DrawFormatString(10, 10, GetColor(255, 255, 255), "RANKING");
	DrawFormatString(10, 110, GetColor(255, 0, 0), "Bボタンでタイトルに戻る");

	//順位の描画
	for (int i = 0; i < RANKING_DATA; ++i)
	{
		DrawFormatString(80, 200 + i * 85, 0xffffff, "No.%d  到達したステージ数", i + 1);
		DrawFormatString(1200, 200 + i * 85, 0xffffff, "%d", score[i]);
	}

}

void RankingScene::Finalize()
{
	StopSoundMem(back_ground_sound);
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

