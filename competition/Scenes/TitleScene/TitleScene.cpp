#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"

TitleScene::TitleScene() : menu_num(0), help(false), is_button(true)
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	//�摜�擾
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{

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

	// �J�[�\����ړ�
	if ((input->GetKeyDown(KEY_INPUT_W) ||
		input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))
		&& !help)
	{
		menu_num--;
		if (menu_num < 0)
		{
			menu_num = 2;
		}
	}

	// �J�[�\�����ړ�
	if ((input->GetKeyDown(KEY_INPUT_S) ||
		input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
		&& !help)
	{
		menu_num++;
		if (menu_num > 2)
		{
			menu_num = 0;
		}
	}

	// �J�[�\������(���肵����ʂɈړ�����)
	if (input->GetKeyDown(KEY_INPUT_E) ||
		input->GetButtonDown(XINPUT_BUTTON_A))
	{
		switch (menu_num)
		{
		case 0:
			return eSceneType::eInGame;
		case 1:
			if (help)
				help = false;
			else
				help = true;
			break;
		case 2:
			return eSceneType::eRanking;
		}
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	int font[3] = { 40,40,40 };
	font[menu_num] = 60;

	// �^�C�g���̑匩�o��
	DrawBox(50, 20, 1230, 420, 0xffffff, TRUE);
	SetFontSize(40);
	DrawFormatString(50, 175, 0x000000, "�Q�[���̖��O(��)");

	/*�V�[���I��*/
	// Start�{�^��(�Q�[�����C���ɑJ�ڂ���)
	DrawBox(480, 435, 800, 510, 0xffffff, TRUE);
	SetFontSize(font[0]);
	DrawFormatString(480, 450, 0x000000, "Game Start");

	// Help�{�^��(�w���v��ʂɑJ�ڂ���)
	DrawBox(480, 525, 800, 600, 0xffffff, TRUE);
	SetFontSize(font[1]);
	DrawFormatString(480, 540, 0x000000, "Help");

	// Ranking�{�^��(�����L���O��ʂɑJ�ڂ���)
	DrawBox(480, 615, 800, 690, 0xffffff, TRUE);
	SetFontSize(font[2]);
	DrawFormatString(480, 630, 0x000000, "Ranking");

	SetFontSize(40);
	DrawFormatString(70, 450, GetColor(255, 255, 255), "�\���{�^��");
	DrawFormatString(70, 500, GetColor(255, 255, 255), "      �J�[�\���ړ�");
	DrawFormatString(70, 580, GetColor(0, 255, 0), "A�@����");

	// ���J�[�\��UI	���Ԃ�����Ύ����܂��B
	switch (menu_num)
	{
		case 0:
			DrawCircle(465, 473, 7, 0xff0000, TRUE);
			break;
		case 1:
			DrawCircle(465, 563, 7, 0xff0000, TRUE);
			break;
		case 2:
			DrawCircle(465, 653, 7, 0xff0000, TRUE);
			break;
		default:
			break;
	}

	if (help)
	{
		SetFontSize(50);
		DrawBox(0, 0, 1280, 720, GetColor(0,150,200), TRUE);
		DrawFormatString(0, 0, 0x000000, "�ꉞ�w���v");
		DrawFormatString(0, 200, 0x000000, "WASD�L�[�ňړ�");
		DrawFormatString(0, 300, 0x000000, "B�{�^���Œe�̔���");
		SetFontSize(40);
		DrawFormatString(70, 580, GetColor(0, 255, 0), "A�@�߂�");
	}
}

void TitleScene::Finalize()
{

}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}