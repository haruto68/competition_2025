#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"

TitleScene::TitleScene()
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

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "�^�C�g���V�[��");
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

	// Ranking�{�^��(�����L���O��ʂɑJ�ڂ���)����������Ȃ��ăG���h�ɂ��Ă��ǂ�
	DrawBox(480, 615, 800, 690, 0xffffff, TRUE);		
	DrawFormatString(480, 630, 0x000000, "Ranking");

}

void TitleScene::Finalize()
{

}

eSceneType TitleScene::GetNowSceneType()const
{
	return eSceneType::eTitle;
}