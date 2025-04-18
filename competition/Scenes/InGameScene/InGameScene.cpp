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
	object_manager->CreateGameObject<Enemy1>(Vector2D(1000, 400));
	object_manager->CreateGameObject<Enemy2>(Vector2D(1000, 400));
	object_manager->CreateGameObject<Enemy3>(Vector2D(1000, 400));
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

//void InGameScene::spawn()
//{
//	/*int ramdom_l = GetRand(2);*/
//	int ramdom_r = GetRand(2);
//	int ramdom_y = GetRand(2);
//
//	// Y���W����
//	float Y_t = 170.0f + (float)(ramdom_y * 80);
//	float Y_b = 170.0f + (3 * 80);
//
//	int num = rand() % 100 + 1;
//
//	// �E���ɓG���X�|�[��������i90%�̊m���j
//	if (num <= 90)
//	{
//		switch (ramdom_r)
//		{
//		case 0:
//			object_manager->CreateGameObject<Enemy1>(Vector2D(620, Y_b));
//			break;
//		case 1:
//			object_manager->CreateGameObject<Enemy2>(Vector2D(620, Y_t));
//			break;
//		case 2:
//			object_manager->CreateGameObject<Enemy3>(Vector2D(620, Y_t));
//			break;
//		default:
//			break;
//		}
//	}
//
//	//// �����ɂ��X�|�[���������Ȃ炱�������L���ɂ���
//	//if (num <= 75)
//	//{
//	//	switch (ramdom_l)
//	//	{
//	//	case 0:
//	//		object_manager->CreateGameObject<Enemy1>(Vector2D(30, Y_b));
//	//		break;
//	//	case 1:
//	//		object_manager->CreateGameObject<Enemy2>(Vector2D(30, Y_t));
//	//		break;
//	//	case 2:
//	//		object_manager->CreateGameObject<Enemy3>(Vector2D(30, Y_t));
//	//		break;
//	//	default:
//	//		break;
//	//	}
//	//}
//}
