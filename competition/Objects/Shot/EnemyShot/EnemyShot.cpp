#include"EnemyShot.h"
#include"../../../Utility/InputManager.h"

EnemyShot::EnemyShot() :
	screen_velocity(0.0),
	shot_image(),
	laser_images(),
	caveat_time(0.0f),
	old_velocity(0.0f)
{

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 座標
	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(10, 10);
	collision.object_type = eObjectType::eEnemyShot;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	// 画像設定
	// レイヤー設定
	z_layer = 1;
	// 可動性設定
	is_mobility = true;

	//画像読み込み
	shot_image[0] = rm->GetImages("Resource/Images/enemy_shot/shot1.png")[0];
	shot_image[1] = rm->GetImages("Resource/Images/enemy_shot/shot2.png")[0];
	shot_image[2] = rm->GetImages("Resource/Images/enemy_shot/shot3.png")[0];
	
	laser_images[0]= rm->GetImages("Resource/Images/GameMaker/Player/Weapon/Laser/Projectile_Player_Laser1.png")[0];
	laser_images[1]= rm->GetImages("Resource/Images/GameMaker/Player/Weapon/Laser/Projectile_Player_Laser2.png")[0];
	laser_images[2]= rm->GetImages("Resource/Images/GameMaker/Player/Weapon/Laser/Projectile_Player_Laser3.png")[0];
	laser_images[3]= rm->GetImages("Resource/Images/GameMaker/Player/Weapon/Laser/Projectile_Player_Laser4.png")[0];
	laser_images[4]= rm->GetImages("Resource/Images/GameMaker/Player/Weapon/Laser/Projectile_Player_Laser5.png")[0];

	exp_num = 2;
}

EnemyShot::~EnemyShot()
{

}

void EnemyShot::Initialize()
{
	turn_target[0] = Vector2D(location.x - 1200, location.y);
	turn_target[1] = Vector2D(location.x - 1200, location.y - 200);
	turn_target[2] = Vector2D(location.x - 1200, location.y + 200);
	turn_target[3] = Vector2D(location.x - 600, location.y);
	turn_target[4] = Vector2D(location.x - 600, location.y);
}

void EnemyShot::Update(float delta_seconds)
{
	birth_count += delta_seconds;

	Movement(delta_seconds);

	Animation();

	if (shot_type == eShotType::eEnemy15)
	{
		caveat_time = 1.75f;
		collision.box_size = Vector2D(1280, 30);
		if (birth_count > caveat_time)
		{
			velocity.x = -3.0f;
		}
	}
}

void EnemyShot::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);

	int image = -1;

	switch (shot_type)
	{
	case eEnemy1:
		image = shot_image[0];
		break;
	case eEnemy2:
		image = shot_image[2];
		break;
	case eEnemy3:
		image = shot_image[2];
		break;
	case eEnemy4:
		image = shot_image[1];
		break;
	case eEnemy5:
		image = shot_image[1];
		break;
	case eEnemy15:
		image = -1;
		if (birth_count < caveat_time)
		{
			//予測線
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
			DrawBox(0, location.y - (collision.box_size.y / 2), 1280, location.y + (collision.box_size.y / 2), GetColor(255, 0, 0), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		//DrawBox(location.x - 640, location.y - (collision.box_size.y / 2), location.x + 640, location.y + (collision.box_size.y / 2), GetColor(205, 205, 205), TRUE);
		
		break;
	default:
		image = shot_image[1];
		break;
	}

	if (image != -1)
	{
		DrawRotaGraph(location.x, location.y, 1.5, 0, image,TRUE);
	}

	if (shot_type == eShotType::eEnemy15)
	{
		DrawRotaGraph(location.x, location.y, 6.0, -(π / 2), laser_images[0], TRUE);
		DrawBox(location.x - 640, location.y - (collision.box_size.y / 2), location.x + 640, location.y + (collision.box_size.y / 2), GetColor(255, 0, 0), false);
	}
	
}

void EnemyShot::Finalize()
{

}

void EnemyShot::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	switch (type)
	{
	case eNone:
		break;
	case ePlayer:
	if(shot_type != eEnemy15)
	{
		object_manager->DestroyGameObject(this);
	}
		break;
	case eEnemy:
		break;
	case ePlayerShot:
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}
}

Vector2D EnemyShot::GetScreenVelocity()
{
	Vector2D value = 0.0f;
	value.x = screen_velocity;
	screen_velocity = 0.0f;
	return value;
}

Vector2D EnemyShot::GetVelocity()
{
	return this->velocity;
}

void EnemyShot::SetVelocity(Vector2D velocity)
{
	this->velocity += velocity;
}

void EnemyShot::Movement(float delta_seconds)
{
	// 移動スピード
	float speed = 200.0f;
	// 移動方向
	Vector2D direction = 0.0f;

	switch (shot_type)
	{
	case eEnemy1:	//真左
		velocity.x = -1.0f;
		break;
	case eEnemy2:	//真上
		velocity.y = -1.0f;
		break;
	case eEnemy3:	//真下
		velocity.y = 1.0f;
		break;
	case eEnemy4:	//自機狙い
		if(location.x > old_player_location.x)
		{
			velocity = Tracking(location, old_player_location) * 1.2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy5:	//自機上狙い(75.0f)
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y - 75.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy6:	//自機下狙い(75.0f)
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y + 75.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy7:	//上から下にカーブ
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y)) * 2;
			velocity.y -= 1.0f;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy8:	//下から上にカーブ
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y)) * 2;
			velocity.y += 1.0f;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy9:	//グネグネ
		velocity.x = -1.0f;
		//
		if (turn_flag[1])
			velocity.y += 0.01f;
		else
			velocity.y -= 0.01f;
		//
		if (velocity.y > 1.0f)
			turn_flag[1] = false;
		else if (velocity.y < -1.0f)
			turn_flag[1] = true;
		break;
	case eEnemy10:
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y - 150.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy11:
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y + 150.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy12:
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y - 225.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy13:
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y + 225.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
			break;
	case eEnemy14:	//自機狙い
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, old_player_location) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy15:
		break;
	case eEnemy16:
		velocity.x = -2.5f;
			break;
	default:
		break;
	}

	
	//位置座標を加速度分減らす
	location += velocity * speed * delta_seconds;

}

void EnemyShot::Animation()
{

}