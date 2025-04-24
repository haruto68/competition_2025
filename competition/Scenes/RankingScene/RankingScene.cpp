#include "RankingScene.h"
#include "../../Utility/InputManager.h"
#include "../../Resource/ResourceManager.h"

RankingScene::RankingScene()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// �摜�擾
}

RankingScene::~RankingScene()
{

}

void RankingScene::Initialize()
{

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

	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "�����L���O�V�[��");

}

void RankingScene::Finalize()
{
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}
