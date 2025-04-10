#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"

InGameScene::InGameScene()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	//�摜�擾
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{

}

eSceneType InGameScene::Update(const float& delta_second)
{
	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//���͏��̍X�V
	input->Update();

	//�C���Q�[���V�[���֑J��
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eResult;
	}

	//�Q�[�����I��
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "�C���Q�[���V�[��");
}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}