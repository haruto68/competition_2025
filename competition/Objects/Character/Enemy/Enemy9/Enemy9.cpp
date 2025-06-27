#include "Enemy9.h"

Enemy9::Enemy9() :
	target(4),
	turn(false),
	birth_count(0.0f)
{

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(60, 60);							//当たり判定の大きさ
	collision.object_type = eObjectType::eEnemy;					//オブジェクトのタイプ
	collision.hit_object_type.push_back(eObjectType::ePlayer);		//ぶつかるオブジェクトのタイプ
	collision.hit_object_type.push_back(eObjectType::ePlayerShot);	//ぶつかるオブジェクトのタイプ
	// 初期スピード
	// speed=200.0f;
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;

	image = rm->GetImages("Resource/Images/enemy/ship22.png")[0];

	exp_num = 5;
}

Enemy9::~Enemy9()
{

}


void Enemy9::Initialize()
{
	velocity.x = -1.0f;

	hp = 35.0f;
}

void Enemy9::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	EnemyShot* shot;
	//時間経過
	birth_count += delta_seconds;
	shot_timer += delta_seconds;
	shot_cooldown = 0.25f;

	if (shot_timer >= shot_cooldown && !explosion_flag)
	{
		switch (target)
		{
		case 1:
			shot = object_manager->CreateGameObject<EnemyShot>(this->location);
			shot->SetShotType(eEnemy12);
			turn = false;
			break;
		case 2:
			shot = object_manager->CreateGameObject<EnemyShot>(this->location);
			shot->SetShotType(eEnemy10);
			break;
		case 3:
			shot = object_manager->CreateGameObject<EnemyShot>(this->location);
			shot->SetShotType(eEnemy5);
			break;
		case 4:
			shot = object_manager->CreateGameObject<EnemyShot>(this->location);
			shot->SetShotType(eEnemy14);
			break;
		case 5:
			shot = object_manager->CreateGameObject<EnemyShot>(this->location);
			shot->SetShotType(eEnemy6);
			break;
		case 6:
			shot = object_manager->CreateGameObject<EnemyShot>(this->location);
			shot->SetShotType(eEnemy11);
			break;
		case 7:
			shot = object_manager->CreateGameObject<EnemyShot>(this->location);
			shot->SetShotType(eEnemy13);
			turn = true;
			break;
		default:
			break;
		}

		PlaySoundMem(soundseffect[1], DX_PLAYTYPE_BACK, TRUE);

		if (turn)
			target--;
		else
			target++;

		//タイマーリセット
		shot_timer = 0.0f;
	}

}

void Enemy9::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 2.0f, 0.0f, image, TRUE);
	}
}

void Enemy9::Finalize()
{

}

void Enemy9::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	switch (type)
	{
	case eNone:
		break;
	case ePlayer:
		break;
	case eEnemy:
		break;
	case ePlayerShot:
		hp -= player_stats.attack_power / 2;
		//PlaySoundMem(soundseffect[0], DX_PLAYTYPE_BACK, TRUE);
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}
}

void Enemy9::Movement(float delta_seconds)
{
	float speed = 200.0f;

	if (location.x <= 1180)
	{
		velocity.x = 0.0f;
		
	}
	if (birth_count > 8.0f)
	{
		velocity.x = 1.0f;
	}

	location += velocity * speed * delta_seconds;
}

void Enemy9::Animation()
{

}