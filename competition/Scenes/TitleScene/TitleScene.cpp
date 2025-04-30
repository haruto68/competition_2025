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

	//�C���Q�[���V�[���֑J��
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eInGame;
	}

	//�Q�[�����I��
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	// �J�[�\����ړ�
	if (input->GetKeyDown(KEY_INPUT_W) && is_button == true)
	{
		menu_num--;
		if (menu_num < 0)
		{
			menu_num = 2;
		}
	}

	// �J�[�\�����ړ�
	if (input->GetKeyDown(KEY_INPUT_S) && is_button == true)
	{
		menu_num++;
		if (menu_num > 2)
		{
			menu_num = 0;
		}
	}

	// �J�[�\������(���肵����ʂɈړ�����)
	if (input->GetKeyDown(KEY_INPUT_1) && is_button == true)
	{
		switch (menu_num)
		{
			case 0:
				return eSceneType::eInGame;
				break;
			case 1:
				// return eSceneType::eInGame;
				help = true;
				is_button = false;
				break;
			case 2:
				return eSceneType::eRanking;
				break;
		}
	}

	if (input->GetKeyDown(KEY_INPUT_2))
	{
		help = false;
		is_button = true;
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	// DrawFormatString(10, 10, GetColor(255, 255, 255), "�^�C�g���V�[��");
	// �^�C�g���̑匩�o��
	DrawBox(50, 20, 1230, 420, 0xffffff, TRUE);
	DrawFormatString(50, 175, 0x000000, "�Q�[���̖��O(��)");

	/*�V�[���I��*/
	// Start�{�^��(�Q�[�����C���ɑJ�ڂ���)
	DrawBox(480, 435, 800, 510, 0xffffff, TRUE);		
	DrawFormatString(480, 450, 0x000000, "Game Start");

	// Help�{�^��(�w���v��ʂɑJ�ڂ���)
	DrawBox(480, 525, 800, 600, 0xffffff, TRUE);		
	DrawFormatString(480, 540, 0x000000, "Help");

	// Ranking�{�^��(�����L���O��ʂɑJ�ڂ���)
	DrawBox(480, 615, 800, 690, 0xffffff, TRUE);		
	DrawFormatString(480, 630, 0x000000, "Ranking");

	DrawFormatString(900, 500, 0xFFFFFF, "�V�[���̔ԍ� %d", menu_num);		// ��

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

	if (menu_num == 1 && help == true)
	{
		DrawBox(0, 0, 1280, 720, 0xff00ff, TRUE);
		DrawFormatString(0, 100, 0x000000, "�ꉞ�w���v�V�[��");
		DrawFormatString(0, 100, 0x000000, "��������y�ѓG��I�u�W�F�N�g�̏ڍא���");
		DrawFormatString(0, 200, 0x000000, "WASD�L�[�ňړ�");
		DrawFormatString(0, 300, 0x000000, "B�{�^���Œe�̔���");
	}
	// �{�^������m�F
	DrawFormatString(800, 600, 0xFFFFFF, "�{�^������̔ԍ� %d", is_button);
	DrawFormatString(900, 500, 0xFFFFFF, "�V�[���̔ԍ� %d", menu_num);
}

void TitleScene::Finalize()
{

}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}