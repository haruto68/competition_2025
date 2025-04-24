#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Objects/GameObjectManager.h"

InGameScene::InGameScene() :
	object_manager(),
	player(),
	back_ground_image(0),
	back_ground_location(0),
	planets_image(),
	pla1(),
	pla2()
{
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	screen_offset.x = -0.02f;

	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	//�w�i
	back_ground_image = rm->GetImages("Resource/Images/back_ground/universe_space02.png")[0];
	back_ground_location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);

	// �f��
	planets_image[0] = rm->GetImages("Resource/Images/Planets/Planet1.png")[0];
	planets_image[1] = rm->GetImages("Resource/Images/Planets/Planet2.png")[0];
	planets_image[2] = rm->GetImages("Resource/Images/Planets/Planet3.png")[0];
	planets_image[3] = rm->GetImages("Resource/Images/Planets/Planet4.png")[0];
	// �f��1
	pla1 = { D_WIN_MAX_X * 1.2,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
	// �f��2
	pla1 = { D_WIN_MAX_X * 0.7,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
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
	Shot* shot;
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 200));
	shot->SetShotType(eEnemy1);
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 400));
	shot->SetShotType(eEnemy2);
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 600));
	shot->SetShotType(eEnemy3);
	shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1000, 300));
	shot->SetShotType(eEnemy3);
	//�X�|�[���J�E���g
	spawn_timer = 0.0f;
}

eSceneType InGameScene::Update(const float& delta_second)
{
	float speed = 1000;
	// �w�i���[�v
	back_ground_location.x -= 0.05f * delta_second * speed;
	if (back_ground_location.x <= -(D_WIN_MAX_X / 2))
		back_ground_location.x = D_WIN_MAX_X / 2;
	speed = 300;
	// �f�����[�v1
	pla1.x -= 0.5 * delta_second * speed;
	if (pla1.x <= -(D_WIN_MAX_X / 2))
	{
		pla1 = { D_WIN_MAX_X * 1.2,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
	}
	// �f�����[�v2
	pla2.x -= 0.5 * delta_second * speed;
	if (pla2.x <= -(D_WIN_MAX_X / 2))
	{
		pla2 = { D_WIN_MAX_X * 1.2,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
	}

	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//���͏��̍X�V
	input->Update();

	//Player��GameObjectManager�C���X�^���X��n��
	player->SetObjectList(object_manager);


	spawn_timer += delta_second;
	if (spawn_timer >= 1.0f) // 1�b���ƂɃX�|�[��
	{
		Spawn();
		spawn_timer = 0.0f;
	}

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
		obj->SetPlayerLocation(player->GetLocation());
		if(obj->GetCollision().object_type != eObjectType::ePlayer)
		{
			obj->SetLocation(Vector2D(obj->GetLocation().x + screen_offset.x, obj->GetLocation().y));
		}
	}

	// ��ʊO�ւł��I�u�W�F�N�g��j�󂷂�
	for (GameObject* obj : scene_objects_list)
	{
		if (obj->GetLocation().x <= -50 || obj->GetLocation().x >= D_WIN_MAX_X + 50 ||
			obj->GetLocation().y <= -50 || obj->GetLocation().y >= D_WIN_MAX_Y + 50)
		{
			object_manager->DestroyGameObject(obj);
		}
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
	DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);
	DrawRotaGraphF(back_ground_location.x + D_WIN_MAX_X, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);

	int bright = 125;
	// �f���`��
	SetDrawBright(bright, bright, bright);
	DrawRotaGraphF(pla1.x, pla1.y, pla1.size, pla1.angle, pla1.image, TRUE);
	DrawRotaGraphF(pla2.x, pla2.y, 0.5, 0.0, pla2.image, TRUE);
	SetDrawBright(255, 255, 255);

	int c = 0;
	// �I�u�W�F�N�g�`��
	for (GameObject* obj : scene_objects_list)
	{
		obj->Draw(screen_offset, false);
		c++;
	}

	SetFontSize(40);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "%d", c);
}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}

void InGameScene::Spawn()        //�G�̎�������
{
	int ramdom_l = GetRand(2);
	int ramdom_r = GetRand(2);

	/*int ramdom_x = GetRand(1);*/
	/*float X1 = 0;*/
	/*int flip = FALSE;*/

	/*switch (ramdom_x)
	{
	case 0:
		X1 = 0.0f; flip = FALSE;
		break;
	case 1:
		X1 = 640.0f; flip = TRUE;
		break;

	default:
		break;
	}*/

	int ramdom_y = GetRand(2);
	float Y_t = 170 + (float)(ramdom_y * 80);
	float Y_b = 170 + (3 * 80);

	int num = rand() % 100 + 1;
	
	if (num <= 90)
	{

		EnemyBase* enemy;
		switch (ramdom_r)
		{
		case 0:
			enemy = object_manager->CreateGameObject<Enemy1>(Vector2D(1300, Y_b));
			enemy->SetObjectList(object_manager);
			break;
		case 1:
			enemy = object_manager->CreateGameObject<Enemy2>(Vector2D(1300, Y_b));
			enemy->SetObjectList(object_manager);
			break;
		case 2:
			enemy = object_manager->CreateGameObject<Enemy3>(Vector2D(1300, Y_b));
			enemy->SetObjectList(object_manager);
			break;
		default:
			break;
		}
	}

	/*if (CheckHitKey(KEY_INPUT_1)) {
		auto enemy = object_manager->CreateGameObject<Enemy1>(Vector2D(1300, Y_b));
		enemy->SetObjectList(object_manager);
	}
	else if (CheckHitKey(KEY_INPUT_2)) {
		auto enemy = object_manager->CreateGameObject<Enemy2>(Vector2D(1300, Y_b));
		enemy->SetObjectList(object_manager);
	}
	else if (CheckHitKey(KEY_INPUT_3)) {
		auto enemy = object_manager->CreateGameObject<Enemy3>(Vector2D(1300, Y_b));
		enemy->SetObjectList(object_manager);
	}*/


}