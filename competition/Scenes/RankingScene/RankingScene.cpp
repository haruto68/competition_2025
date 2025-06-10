#include "RankingScene.h"
#include "../../Utility/InputManager.h"
#include "../../Resource/ResourceManager.h"

RankingScene::RankingScene() : back_ground_sound(NULL), score{}, rank{}
{
	// //���\�[�X�Ǘ��C���X�^���X�擾
	// ResourceManager* rm = ResourceManager::GetInstance();
	// 
	// // �摜�擾

	sounds_effect[0] = NULL;
	sounds_effect[1] = NULL;
}

RankingScene::~RankingScene()
{

}

void RankingScene::Initialize()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// �摜�擾

	// �����擾
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM/Title/Title.mp3");
	// �{�^�����艹
	sounds_effect[0] = rm->GetSounds("Resource/Sounds/SoundsEffect/Button/button_enter.mp3");
	// �I����
	sounds_effect[1] = rm->GetSounds("Resource/Sounds/SoundsEffect/Button/button_select.mp3");
	// �����̉��ʂ̐ݒ�
	ChangeVolumeSoundMem(100, back_ground_sound);
	// �{�^�����艹�̉��ʂ̐ݒ�
	ChangeVolumeSoundMem(200, sounds_effect[0]);
	// �I�����̉��ʂ̐ݒ�
	ChangeVolumeSoundMem(200, sounds_effect[1]);
	// �����̍Đ�
	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_LOOP, TRUE);


	// �����L���O�f�[�^�̓ǂݍ���
	FILE* fp = nullptr;

	// �t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/data/ranking.txt", "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/ranking_data.txt���J���܂���ł���\n");
	}

	// �Ώۃt�@�C�������݂���
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fscanf_s(fp, "%d %d",&rank[i],  & score[i]);
	}

	// �t�@�C���N���[�Y
	fclose(fp);
}

eSceneType RankingScene::Update(const float& delta_second)
{
	// ���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	// ���͏��̍X�V
	input->Update();

	// �Q�[���I��
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	// 2�L�[�Ń^�C�g���ɖ߂�
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
	DrawFormatString(10, 110, GetColor(255, 0, 0), "B�{�^���Ń^�C�g���ɖ߂�");

	//���ʂ̕`��
	for (int i = 0; i < RANKING_DATA; ++i)
	{
		DrawFormatString(80, 200 + i * 85, 0xffffff, "No.%d  ���B�����X�e�[�W��", i + 1);
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

	// ���ʂ𐮗񂳂���
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


	// �����L���O�f�[�^�̓ǂݍ���
	FILE* fp = nullptr;

	// �t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/data/ranking.txt", "w");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/data/ranking.txt���J���܂���ł���\n");
	}

	// �Ώۃt�@�C���ɏ�������
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fprintf(fp, "%d %d\n", rank[i], score[i]);
	}

	// �t�@�C���N���[�Y
	fclose(fp);
}


void RankingScene::SetRank(int score)
{
	//3�ʂ��珇�ʂ�ݒ肷��
	if (this->score[RANKING_DATA - 1] < score)
	{
		if (this->score[RANKING_DATA - 2] != score && this->score[RANKING_DATA - 3] != score)
		{
			this->score[RANKING_DATA - 1] = score;
			SortData();
		}
	}

}

