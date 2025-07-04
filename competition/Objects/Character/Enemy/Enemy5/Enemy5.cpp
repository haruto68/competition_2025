#include "Enemy5.h"

Enemy5::Enemy5() :
	shot_num(0),
	cool_down_2(3.0f),
	cool_down_2_count(0.0f)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(30, 30);							//当たり判定の大きさ
	collision.object_type = eObjectType::eEnemy;					//オブジェクトのタイプ
	collision.hit_object_type.push_back(eObjectType::ePlayer);		//ぶつかるオブジェクトのタイプ
	collision.hit_object_type.push_back(eObjectType::ePlayerShot);	//ぶつかるオブジェクトのタイプ
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;

	//画像読み込み
	image = rm->GetImages("Resource/Images/enemy/ship5.png")[0];

	exp_num = 2;
}

Enemy5::~Enemy5()
{
}

void Enemy5::Initialize()
{
	//　仮敵2のサイズ(大きさ)
	collision.box_size = Vector2D(25.0f, 25.0f);
	// 仮テキの速さ
	speed = 200.0f;

	hp = 9.0f;

	velocity.x = -0.8f;
}

void Enemy5::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	float shot_cooldown = 0.8f;

	int shot_num_max = 2;

	//時間経過
	shot_timer += delta_seconds;
	
	if(shot_num > shot_num_max)
	{
		cool_down_2_count += delta_seconds;
	}
	if (cool_down_2_count >= cool_down_2)
	{
		shot_num = 0;
		cool_down_2_count = 0.0f;
	}

	if (shot_timer >= shot_cooldown && shot_num <= shot_num_max
		&& player_location.x < location.x && !explosion_flag)
	{
		EnemyShot* shot = object_manager->CreateGameObject<EnemyShot>(this->location);
		shot->SetShotType(eEnemy4);

		shot_num++;

		PlaySoundMem(soundseffect[1], DX_PLAYTYPE_BACK, TRUE);

		//タイマーリセット
		shot_timer = 0.0f;
	}
}

void Enemy5::Draw(const Vector2D&, bool) const
{

	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, 0.0f, image, TRUE);
	}

}

void Enemy5::Finalize()
{
}

void Enemy5::OnHitCollision(GameObject* hit_object)
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

void Enemy5::Movement(float delta_seconds)
{
	if (location.x <= 1180)
	{
		velocity.x = -0.2f;
	}

	location += velocity * speed * delta_seconds;
}

void Enemy5::Animation()
{
}