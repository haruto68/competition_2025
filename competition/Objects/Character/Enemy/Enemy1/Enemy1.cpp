#include "Enemy1.h"

Enemy1::Enemy1()
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

	//画像読み込み
	image = rm->GetImages("Resource/Images/enemy/ship1.png")[0];

	exp_num = 1;
}

Enemy1::~Enemy1()
{

}


void Enemy1::Initialize()
{
	int random = rand() % 2;
	if (random == 0)
		velocity.y = -1.0f;
	else
		velocity.y = 1.0f;

	velocity.x = -0.5f;

}

void Enemy1::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//時間経過
	shot_timer += delta_seconds;

	if (shot_timer>=shot_cooldown)
	{
		EnemyShot* shot = object_manager->CreateGameObject<EnemyShot>(this->location);
		shot->SetShotType(eEnemy1);
		PlaySoundMem(soundseffect[1], DX_PLAYTYPE_BACK, TRUE);

		//タイマーリセット
		shot_timer = 0.0f;

		int random_cool = rand() % 5;

		switch (random_cool)
		{
		case 0:
			shot_cooldown = 1.2f;
			break;
		case 1:
			shot_cooldown = 1.2f;
			break;
		case 2:
			shot_cooldown = 1.3f;
			break;
		case 3:
			shot_cooldown = 1.5f;
			break;
		case 4:
			shot_cooldown = 1.6f;
			break;
		default:
			break;
		}
	}

}

void Enemy1::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, 0.0f, image, TRUE);
	}
}

void Enemy1::Finalize()
{
}

void Enemy1::OnHitCollision(GameObject* hit_object)
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

void Enemy1::Movement(float delta_seconds)
{
	float speed = 200.0f;

	if ((location.y + velocity.y) <= (65.0f + collision.box_size.y) || (location.y + velocity.y) >= (680 - collision.box_size.y))
	{
		
		if (velocity.y < 0)
			velocity.y = 1.0f;
		else
			velocity.y = -1.0f;
	}

	location += velocity * speed * delta_seconds;
}

void Enemy1::Animation()
{

}