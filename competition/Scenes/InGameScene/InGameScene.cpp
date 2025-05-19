#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Objects/GameObjectManager.h"
#include"../../Objects/Character/Player/Player.h"

InGameScene::InGameScene() :
	object_manager(nullptr),
	player(),
	boss(),
	level_up_ui(),
	hp_ui(),
	level_ui(),
	back_ground_image(0),
	back_ground_location(0),
	planets_image(),
	pla1(),
	pla2(),
	spawn_timer(0),
	boss_flag(),
	player_old_level(1),
	up_grade_stock(0),
	level_up_flg(),
	time_stop(),
	time_count(60)
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
	pla1 = { D_WIN_MAX_X * 1.5,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
	// �f��2
	pla1 = { D_WIN_MAX_X * 1.0,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
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

	//
	level_up_ui = new LevelUpUI();
	level_up_ui->Initialize();

	// Test�p����
	hp_ui = new HpUI();
	hp_ui->Initialize();

	level_ui = new LevelUI();
	level_ui->Initialize();
	
	
	/*object_manager->CreateGameObject<Boss1>(Vector2D(1200, 400));*/
}

eSceneType InGameScene::Update(const float& delta_second)
{
	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//���͏��̍X�V
	input->Update();

	//���x���A�b�vUI�X�V����
	level_up_ui->Update(level_up_flg);


	level_ui->SetExperience(player->GetPlayerStats().current_exp, player->GetPlayerStats().next_level_exp);
	level_ui->Update();
	hp_ui->SetHp(player->GetPlayerStats().life_count, 6);


	// �V�[�����I�u�W�F�N�g�X�V
	if(!time_stop)
	{
		//�^�C���J�E���g	
		if(time_count >= 0.0f)
		{
			time_count -= (delta_second * 1.0f);
		}
		else if (!boss_flag)
		{
			//�{�X����
			boss_flag = true;
			boss = object_manager->CreateGameObject<Boss1>(Vector2D(1200, 400));
		}

		// �w�i�Ǘ�����
		BackGroundManager(delta_second);

		// �G�����Ǘ�����
		EnemyManager(delta_second);

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
			// �v���C���[���W�󂯓n��
			obj->SetPlayerLocation(player->GetLocation());
			//�v���C���[�X�e�[�^�X�󂯓n��
			obj->SetPlayerStats(player->GetPlayerStats());
			// �I�u�W�F�N�g���X�N���[���ƈꏏ�ɓ���������
			if (obj->GetCollision().object_type != eObjectType::ePlayer)
			{
				obj->SetLocation(Vector2D(obj->GetLocation().x + screen_offset.x, obj->GetLocation().y));
			}
			// �I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X�����n��
			if (obj->CheckInstance() == nullptr)
			{
				obj->SetInstance(object_manager);
			}
		}

		//�����蔻��`�F�b�N����
		for (int a = 0; a < scene_objects_list.size(); a++)
		{
			for (int b = 0; b < scene_objects_list.size(); b++)
			{
				object_manager->HitCheck(scene_objects_list[a], scene_objects_list[b]);
				object_manager->HitCheck(scene_objects_list[b], scene_objects_list[a]);
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
	}
	else
	{
		//�J�[�\����
		if (input->GetKeyUp(KEY_INPUT_A) || input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
		{
			if (level_up_ui->cursor == 0)
			{
				level_up_ui->cursor = 2;
			}
			else if (level_up_ui->cursor == 1)
			{
				level_up_ui->cursor = 0;
			}
			else
			{
				level_up_ui->cursor = 1;
			}
		}
		//�J�[�\���E
		if (input->GetKeyUp(KEY_INPUT_D) || input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
		{
			if (level_up_ui->cursor == 0)
			{
				level_up_ui->cursor = 1;
			}
			else if (level_up_ui->cursor == 1)
			{
				level_up_ui->cursor = 2;
			}
			else
			{
				level_up_ui->cursor = 0;
			}
		}
		//�J�[�\������
		if (input->GetKeyUp(KEY_INPUT_E) || input->GetButtonDown(XINPUT_BUTTON_A))
		{
			//�������e�擾
			ePowerUp strengthen = level_up_ui->GetLottery();
			//����
			player->StatsUp(strengthen);
			time_stop = false;
			level_up_flg = false;

			up_grade_stock--;
		}
	}

	//�A�b�v�O���[�h
	if ((input->GetKeyUp(KEY_INPUT_L) ||
		input->GetButtonDown(XINPUT_BUTTON_START))
		&& up_grade_stock > 0)
	{
		if (level_up_flg)
			level_up_flg = false;
		else
			level_up_flg = true;
		if (time_stop)
			time_stop = false;
		else
			time_stop = true;
	}
	//���x���A�b�v��
	if (player->GetPlayerStats().player_level != player_old_level)
	{
		up_grade_stock++;
	}
	player_old_level = player->GetPlayerStats().player_level;

	//���U���g�V�[���֑J��
	if (input->GetKeyUp(KEY_INPUT_SPACE) ||
		player->GetPlayerStats().life_count <= 0)
	{
		return eSceneType::eResult;
	}

	//�����L���O�V�[���֑J��
	if (boss != nullptr && boss->GetBoss1Hp() <= 0)
	{
		return eSceneType::eRanking;
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
	DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);
	DrawRotaGraphF(back_ground_location.x + D_WIN_MAX_X, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �f���`��
	int bright = 125;
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

	////////////////////////////////////////////////////////////////////////////////////////////////////

	//UI�]�[��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, 1280, 80, GetColor(50, 0, 100), TRUE);
	DrawBox(0, 680, 1280, 720, GetColor(50, 0, 100), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	//�^�C���J�E���g
	SetFontSize(70);
	if(time_count > 0)
	{
		DrawFormatString(1100, 10, GetColor(255, 255, 255), "%.1f", time_count);
	}

	// �v���C���[��HP�̃e�[�u��HP�o�[�̕`��
	hp_ui->Draw();
	// ���x��UI�o�[�̕`��
	level_ui->Draw();

	if (up_grade_stock > 0)
	{
		SetFontSize(40);
		DrawFormatString(475, 680, GetColor(255, 0, 255), "Start to UpGrade");
	}

	//���x���A�b�vUI�`��
	if (level_up_flg)
	{
		level_up_ui->Draw(player->GetPlayerStats());
	}

}

void InGameScene::Finalize()
{
	level_up_ui->Finalize();
	hp_ui->Finalize();
	level_ui->Finalize();
}

eSceneType InGameScene::GetNowSceneType()const
{
	return eSceneType::eInGame;
}

void InGameScene::BackGroundManager(const float& delta_second)
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
		pla1 = { D_WIN_MAX_X * 1.5,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
	}
	// �f�����[�v2
	pla2.x -= 0.5 * delta_second * speed;
	if (pla2.x <= -(D_WIN_MAX_X / 2))
	{
		pla2 = { D_WIN_MAX_X * 1.5,float(rand() % 720),((double)rand() / RAND_MAX) + 0.7,0.0,planets_image[rand() % 4] };
	}
}

void InGameScene::EnemyManager(const float& delta_second)
{
	// �G�����N�[���^�C��
	spawn_timer += delta_second;
	if (spawn_timer >= 2.0f) // �b���ƂɃX�|�[��
	{
		Spawn();
		spawn_timer = 0.0f;
	}
}

void InGameScene::Spawn()        //�G�̎�������
{
	int ramdom_l = GetRand(2);
	int ramdom_r = GetRand(6);

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


	/*int ramdom_y = GetRand(6);*/
	/*float Y_t = 170 + (float)(ramdom_y * 80);*/
	/*float Y_b = 170 + (3 * 80);*/

	int num = rand() % 100 + 1;
	
	if (num <= 99)
	{
		  
		EnemyBase* enemy;
		switch (ramdom_r)
		{
		case 0:
			enemy = object_manager->CreateGameObject<Enemy1>(Vector2D(1300, 400));//�W�O�U�O
			break;
		case 1:
			enemy = object_manager->CreateGameObject<Enemy2>(Vector2D(1300, 665));//��C
			break;
		case 2:
			enemy = object_manager->CreateGameObject<Enemy3>(Vector2D(1300, 400));//���U�A�^��
			break;
		case 3:
			enemy = object_manager->CreateGameObject<Enemy3>(Vector2D(1300, 200));//���U�A��
			break;
		case 4:
			enemy = object_manager->CreateGameObject<Enemy3>(Vector2D(1300, 600));//���U�A��
			break;
		case 5:
			object_manager->CreateGameObject<Enemy2>(Vector2D(1300, 95))->SetTrans();//��C�A�t
			break;
		case 6:
			object_manager->CreateGameObject<Enemy2>(Vector2D(1300, 95))->SetTrans();//��C�A�t
			enemy = object_manager->CreateGameObject<Enemy2>(Vector2D(1300, 665));//��C
			break;
		default:
			break;
		}
	}

	//if (time_count == 0)
	//{
	//	object_manager->CreateGameObject<Boss1>(Vector2D(1200, 400));
	//}


	if (CheckHitKey(KEY_INPUT_0)) {
		auto enemy = object_manager->CreateGameObject<Enemy1>(Vector2D(1300, 400));
	}
	else if (CheckHitKey(KEY_INPUT_1)) {
		auto enemy = object_manager->CreateGameObject<Enemy2>(Vector2D(1300, 665));
	}
	else if (CheckHitKey(KEY_INPUT_2)) {
		auto enemy = object_manager->CreateGameObject<Enemy3>(Vector2D(1300, 400));
	}
	else if (CheckHitKey(KEY_INPUT_3)) {
		auto enemy = object_manager->CreateGameObject<Enemy3>(Vector2D(1300, 200));
	}
	else if (CheckHitKey(KEY_INPUT_4)) {
		auto enemy = object_manager->CreateGameObject<Enemy3>(Vector2D(1300, 600));
	}
	else if (CheckHitKey(KEY_INPUT_5)) {
		 object_manager->CreateGameObject<Enemy2>(Vector2D(1300, 95))->SetTrans();
	}
	else if (CheckHitKey(KEY_INPUT_6)) {
		object_manager->CreateGameObject<Enemy2>(Vector2D(1300, 95))->SetTrans();
		auto enemy = object_manager->CreateGameObject<Enemy2>(Vector2D(1300, 665));
	}
	else if (CheckHitKey(KEY_INPUT_7)) {
		auto enemy = object_manager->CreateGameObject<Boss1>(Vector2D(1200, 400));
	}


}