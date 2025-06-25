#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
#include <Windows.h>

TitleScene::TitleScene() : menu_num(0), help(false), is_button(true), back_ground_sound(NULL), back_ground_image(), font{}
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	// ResourceManager* rm = ResourceManager::GetInstance();

	// �摜�擾
	// �����擾
	// back_ground_sound = rm->GetSounds("Resource/Sounds/BGM/Title/Title.mp3");
	sounds_effect[0] = NULL;
	sounds_effect[1] = NULL;

	back_ground_location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// UI�摜�̊i�[
	ui_button.push_back(rm->GetImages("Resource/Images/Buttons/steamcontroller/steam_dpad.png")[0]);
	ui_button.push_back(rm->GetImages("Resource/Images/Buttons/steamcontroller/steam_button_color_a.png")[0]);
	ui_button.push_back(rm->GetImages("Resource/Images/Buttons/steamcontroller/steam_button_color_b.png")[0]);

	// �摜�̈ʒu���W�̐ݒ�
	ui_location.push_back(Vector2D(32, D_WIN_MAX_Y - 32));
	ui_location.push_back(Vector2D(((D_WIN_MAX_X / 2) + 200), D_WIN_MAX_Y - 32));

	// �t�H���g�̍��W�̐ݒ�
	font_location.push_back(Vector2D(64, D_WIN_MAX_Y - 50));
	font_location.push_back(Vector2D(904, D_WIN_MAX_Y - 50));


	// �摜�擾
	back_ground_image = rm->GetImages("Resource/Images/back_ground/universe_asteroid03.png")[0];		// �w�i�摜
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
	
	// �t�H���g��ݒ肷��
	// title_name = CreateFontToHandle("�������ۃS�V�b�N", 150, 6);
	// button = CreateFontToHandle("�������ۃS�V�b�N", 40, 6);
	// push_button = CreateFontToHandle("�������ۃS�V�b�N", 60, 6);

	// �w���v��ʂ̃t�H���g�̐ݒ�
	// help_font = CreateFontToHandle("�������ۃS�V�b�N", 50, 6);
	// help_font_title = CreateFontToHandle("�������ۃS�V�b�N", 70, 6);

	// �t�H���g�̐ݒ�
	font[0] = CreateFontToHandle("�������ۃS�V�b�N", 40, 6);
	font[1] = CreateFontToHandle("�������ۃS�V�b�N", 50, 6);
	font[2] = CreateFontToHandle("�������ۃS�V�b�N", 60, 6);
	font[3] = CreateFontToHandle("�������ۃS�V�b�N", 70, 6);
	font[4] = CreateFontToHandle("�������ۃS�V�b�N", 150, 6);


	//�����擾(0: �G���j�󎞂̉� 1: �G���e�����������̉�)
	rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemybreak.mp3");
	rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemyshot.mp3");
}

eSceneType TitleScene::Update(const float& delta_second)
{
	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//���͏��̍X�V
	input->Update();

	//�Q�[�����I��
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	// �w���v���J����Ă���Ƒ�����~����
	if (help != true)
	{
		// �J�[�\����ړ�
		if ((input->GetButtonDown(XINPUT_BUTTON_DPAD_UP) || input->GetKeyDown(KEY_INPUT_W)) && is_button == true)
		{
			PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

			menu_num--;
			if (menu_num < 0)
			{
				menu_num = 2;
			}
		}

		// �J�[�\�����ړ�
		if ((input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || input->GetKeyDown(KEY_INPUT_S)) && is_button == true)
		{
			PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

			menu_num++;
			if (menu_num > 2)
			{
				menu_num = 0;
			}
		}

	}

	// �J�[�\������(���肵����ʂɈړ�����)
	if ((input->GetButtonDown(XINPUT_BUTTON_A) || (input->GetKeyDown(KEY_INPUT_E) || input->GetKeyDown(KEY_INPUT_1))) && is_button == true)
	{
		switch (menu_num)
		{
		case 0:
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_BACK, TRUE);
			return eSceneType::eInGame;
		case 1:
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_BACK, TRUE);
			if (help)
				help = false;
			else
				help = true;
			break;
		case 2:
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_NORMAL, TRUE);
			return eSceneType::eExit;
		}
	}

	if (input->GetButtonDown(XINPUT_BUTTON_B) || input->GetKeyDown(KEY_INPUT_2))
	{
		PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_BACK, TRUE);
		help = false;
		is_button = true;
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	// �w�i�摜
	DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);

	// int font[3] = { 40,40,40 };
	// font[menu_num] = 60;

	// �^�C�g���̑匩�o��
	// DrawBox(50, 20, 1230, 420, 0xffffff, TRUE);
	// SetFontSize(150);

	// DrawFormatString(100, 175, 0xffffff, "Nebula striker");

	/*�V�[���I��*/
	// Start�{�^��(�Q�[�����C���ɑJ�ڂ���)
	// DrawBox(480, 435, 800, 510, 0xffffff, TRUE);
	// SetFontSize(font[0]);
	// DrawFormatString(480, 450, 0xffffff, "Game Start");

	// Help�{�^��(�w���v��ʂɑJ�ڂ���)
	// DrawBox(480, 525, 800, 600, 0xffffff, TRUE);
	// SetFontSize(font[1]);
	// DrawFormatString(480, 540, 0xffffff, "Help");

	// Ranking�{�^��(�����L���O��ʂɑJ�ڂ���)
	// DrawBox(480, 615, 800, 690, 0xffffff, TRUE);
	// SetFontSize(font[2]);
	// DrawFormatString(480, 630, 0xffffff, "Ranking");

	// SetFontSize(40);
	// DrawFormatString(65, 450, GetColor(255, 255, 255), "�\���{�^��");
	// DrawFormatString(65, 500, GetColor(255, 255, 255), "      �J�[�\���ړ�");
	// DrawFormatString(65, 580, GetColor(0, 255, 0), "A�@����");
	
	// �^�C�g���̕`��
	// DrawStringToHandle(100, 175, "Nebula Striker", GetColor(255, 0, 255), title_name);
	DrawStringToHandle(100, 175, "Nebula Striker", GetColor(255, 0, 255), font[4]);

	// �\���L�[�ŃJ�[�\���ړ�
	DrawRotaGraphF(ui_location[0].x, ui_location[0].y, 0.5, 0.0, ui_button[0], TRUE);
	// DrawStringToHandle(font_location[0].x, font_location[0].y, "�J�[�\���ړ�", GetColor(255, 0, 255), button);
	DrawStringToHandle(font_location[0].x, font_location[0].y, "�J�[�\���ړ�", GetColor(255, 0, 255), font[0]);

	// A�{�^���Ō���
	DrawRotaGraphF(ui_location[1].x, ui_location[1].y, 0.5, 0.0, ui_button[1], TRUE);
	// DrawStringToHandle(font_location[1].x, font_location[1].y, "����", GetColor(255, 0, 255), button);
	DrawStringToHandle(font_location[1].x, font_location[1].y, "����", GetColor(255, 0, 255), font[0]);

	// ���J�[�\��UI	
	switch (menu_num)
	{
		case 0:
			DrawCircle(465, 473, 7, 0xff0000, TRUE);
			DrawStringToHandle(480, 450, "Game Start", GetColor(255, 0, 0), font[2]);
			DrawStringToHandle(480, 540, "Help", GetColor(255, 0, 255), font[0]);
			DrawStringToHandle(480, 630, "End", GetColor(255, 0, 255), font[0]);
			break;
		case 1:
			DrawCircle(465, 563, 7, 0xff0000, TRUE);
			DrawStringToHandle(480, 450, "Game Start", GetColor(255, 0, 255), font[0]);
			DrawStringToHandle(480, 540, "Help", GetColor(255, 0, 0), font[2]);
			DrawStringToHandle(480, 630, "End", GetColor(255, 0, 255), font[0]);
			break;
		case 2:
			DrawCircle(465, 653, 7, 0xff0000, TRUE);
			DrawStringToHandle(480, 450, "Game Start", GetColor(255, 0, 255), font[0]);
			DrawStringToHandle(480, 540, "Help", GetColor(255, 0, 255), font[0]);
			DrawStringToHandle(480, 630, "End", GetColor(255, 0, 0), font[2]);
			break;
		default:
			break;
	}

	if (help)
	{
		// SetFontSize(50);
		DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);
		// DrawFormatString(0, 0, 0xffffff, "HELP");
		// DrawFormatString(0, 200, 0xffffff, "�E���X�e�B�b�N�ňړ�");
		// DrawFormatString(0, 300, 0xffffff, "�EB�{�^���Œe�̔���");
		// DrawFormatString(0, 400, 0xffffff, "�EY�{�^���ŃA�b�v�O���[�h");
		// DrawFormatString(0, 500, 0x000000, "B�{�^���Ń^�C�g���ɖ߂�");
		SetFontSize(40);
		
		// test
		DrawStringToHandle(10, 10, "HELP", GetColor(255, 0, 255), font[3]);
		DrawStringToHandle(10, 210, "���X�e�B�b�N�ړ�", GetColor(255, 0, 255), font[1]);
		DrawStringToHandle(10, 310, "B�{�^���Œe�̔���", GetColor(255, 0, 255), font[1]);
		DrawStringToHandle(10, 410, "Y�{�^���ŃA�b�v�O���[�h", GetColor(255, 0, 255), font[1]);
		DrawRotaGraphF(870, 685, 0.5, 0.0, ui_button[2], TRUE);
		DrawStringToHandle(900, 660, "�^�C�g���ɖ߂�", 0xff00ff, font[1]);
		// DrawStringToHandle(0, 400, "HELP", 0xfff00ff, help_font);
	}
}

void TitleScene::Finalize()
{
	// BGM�̍Đ����~�߂�
	StopSoundMem(back_ground_sound);

	// �ݒ肵���t�H���g���폜����
	for (int i = 0; i < 5; i++)
	{
		DeleteFontToHandle(font[i]);
	}
}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}