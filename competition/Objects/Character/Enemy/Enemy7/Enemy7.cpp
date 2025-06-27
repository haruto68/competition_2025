#include "Enemy7.h"

Enemy7::Enemy7()
{

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(30, 30);							//当たり判定の大きさ
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

	image = rm->GetImages("Resource/Images/enemy/ship21.png")[0];

	exp_num = 3;
}

Enemy7::~Enemy7()
{

}


void Enemy7::Initialize()
{
	int random = rand() % 2;
	if (random == 0)
		velocity.y = -1.0f;
	else
		velocity.y = 1.0f;

	velocity.x = -1.2f;

	hp = 25.0f;
}

void Enemy7::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	EnemyShot* shot;
	//時間経過
	shot_timer += delta_seconds;

	if (shot_timer >= shot_cooldown && location.x > player_location.x + 200.0f && !explosion_flag)
	{
		shot = object_manager->CreateGameObject<EnemyShot>(this->location);
		shot->SetShotType(eEnemy10);
		shot = object_manager->CreateGameObject<EnemyShot>(this->location);
		shot->SetShotType(eEnemy11);
		PlaySoundMem(soundseffect[1], DX_PLAYTYPE_BACK, TRUE);

		//タイマーリセット
		shot_timer = 0.0f;

		int random_cool = rand() % 5;

		switch (random_cool)
		{
		case 0:
			shot_cooldown = 1.4f;
			break;
		case 1:
			shot_cooldown = 1.5f;
			break;
		case 2:
			shot_cooldown = 1.6f;
			break;
		case 3:
			shot_cooldown = 1.7f;
			break;
		case 4:
			shot_cooldown = 1.8f;
			break;
		default:
			break;
		}
	}

}

void Enemy7::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, 0.0f, image, TRUE);
	}
}

void Enemy7::Finalize()
{

}

void Enemy7::OnHitCollision(GameObject* hit_object)
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

void Enemy7::Movement(float delta_seconds)
{
	float speed = 200.0f;

	if (location.x >= 1290)
		velocity.x = -0.1f;
	else
		velocity.x = -0.85f;

	if ((location.y + velocity.y) <= (65.0f + collision.box_size.y) || (location.y + velocity.y) >= (680 - collision.box_size.y))
	{

		if (velocity.y < 0)
			velocity.y = 1.0f;
		else
			velocity.y = -1.0f;
	}

	location += velocity * speed * delta_seconds;
}

void Enemy7::Animation()
{

}