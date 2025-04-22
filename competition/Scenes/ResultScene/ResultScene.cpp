#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"

ResultScene::ResultScene()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	//�摜�擾
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{

}

eSceneType ResultScene::Update(const float& delta_second)
{
	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//���͏��̍X�V
	input->Update();

	//�C���Q�[���V�[���֑J��
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eTitle;
	}

	//�Q�[�����I��
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	return GetNowSceneType();
}

void ResultScene::Draw() const
{
		DrawFormatString(10, 10, GetColor(255, 255, 255), "���U���g�V�[��");
		/*		���U���g��ʈ�*/
		// �����N
		DrawBox(50, 20, 615, 550, 0xffffff, TRUE);
		DrawFormatString(50, 270, 0x000000, "�X�R�A�����N");

		// �X�R�A����
		DrawBox(665, 20, 1230, 550, 0xffffff, TRUE);
		DrawFormatString(665, 270, 0x000000, "�X�R�A����");

		// �G���h�{�^��
		DrawBox(25, 600, 325, 700, 0xffffff, TRUE);
		DrawFormatString(25, 630, 0xff0000, "End");

		// �l�N�X�g�ڃ^��
		DrawBox(955, 600, 1255, 700, 0xffffff, TRUE);
		DrawFormatString(955, 630, 0x0000ff, "Next");
	
}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}