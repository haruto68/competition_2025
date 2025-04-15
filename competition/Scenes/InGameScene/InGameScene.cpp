#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Objects/GameObjectManager.h"

InGameScene::InGameScene() :
	object_manager(),
	player(),
	shot()
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
	//GameObjectManager�C���X�^���X�擾
	object_manager = new GameObjectManager();

	//�v���C���[����
	player = object_manager->CreateGameObject<Player>(Vector2D(160, 360));

	// Test�p����
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 200));
	shot->SetShotType(eEnemy1);
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 400));
	shot->SetShotType(eEnemy2);
	// ���ɐ�������Ƃ��͂��̉���
	enemy1 = object_manager->CreateGameObject<Enemy1>(Vector2D(1000, 400));
}

eSceneType InGameScene::Update(const float& delta_second)
{
	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//���͏��̍X�V
	input->Update();

	// ��������I�u�W�F�N�g�̊m�F
	object_manager->CheckCreateObject();
	// �j������I�u�W�F�N�g�̊m�F
	object_manager->CheckDestroyObject();
	// ���݂̃I�u�W�F�N�g���X�g���擾
	scene_objects_list = object_manager->GetObjectList();

	// ���X�g���̃I�u�W�F�N�g���X�V����
	for (GameObject* obj : scene_objects_list)
	{
		obj->Update(delta_second);
	}



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
	// �w�i�`��
	DrawBox(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, GetColor(0, 0, 100), TRUE);

	// �I�u�W�F�N�g�`��
	for (GameObject* obj : scene_objects_list)
	{
		obj->Draw(screen_offset, false);
	}

	DrawFormatString(10, 10, GetColor(255, 255, 255), "�C���Q�[���V�[��");
}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}