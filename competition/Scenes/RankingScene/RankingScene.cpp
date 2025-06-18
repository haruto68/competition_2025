#include "RankingScene.h"
#include "../../Utility/InputManager.h"
#include "../../Resource/ResourceManager.h"

RankingScene::RankingScene() : back_ground_sound(NULL), score{}, rank{}, font{}
{
	// //���\�[�X�Ǘ��C���X�^���X�擾
	// ResourceManager* rm = ResourceManager::GetInstance();
	
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
	back_ground_image = rm->GetImages("Resource/Images/back_ground/universe_asteroid03.png")[0];		// �w�i�摜
	button_image.push_back(rm->GetImages("Resource/Images/Buttons/steamcontroller/steam_button_color_b.png")[0]);
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

	back_ground_location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);

	// �t�H���g�̓o�^
	// font.push_back(CreateFontToHandle("�������ۃS�V�b�N", 70, 6));
	// font.push_back(CreateFontToHandle("�������ۃS�V�b�N", 50, 6));

	font[0] = CreateFontToHandle("�������ۃS�V�b�N", 70, 6);
	font[1] = CreateFontToHandle("�������ۃS�V�b�N", 50, 6);

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
	// �w�i�摜
	DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);

	// DrawFormatString(10, 10, GetColor(255, 255, 255), "RANKING");
	// DrawFormatString(10, 110, GetColor(255, 0, 0), "B�{�^���Ń^�C�g���ɖ߂�");

	DrawStringToHandle(10, 10, "RANKING", GetColor(255, 255, 255), font[0]);
	// DrawStringToHandle(10, 110, "B�{�^���Ń^�C�g���ɖ߂�", GetColor(255, 255, 255), font[0]);

	char buf[128];

	//���ʂ̕`��
	for (int i = 0; i < RANKING_DATA; ++i)
	{

		// DrawFormatString(80, 200 + i * 85, 0xffffff, "No.%d  ���B�����X�e�[�W��", i + 1);
		// DrawFormatString(1200, 200 + i * 85, 0xffffff, "%d", score[i]);
		snprintf(buf, sizeof(buf), "No.%d ���B�����X�e�[�W��", i + 1);
		DrawStringToHandle(80, 90 + i * 200, buf, GetColor(255, 255, 255), font[1]);

		snprintf(buf, sizeof(buf), "%d", score[i]);
		DrawStringToHandle(1200, 90 + i * 200, buf, GetColor(255, 255, 255), font[1]);
	}
	DrawRotaGraphF(870, 685, 0.5, 0.0, button_image[0], TRUE);
	DrawStringToHandle(900, 660, "�^�C�g���ɖ߂�", 0xffffff, font[1]);

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

