#include "Boss1.h"

Boss1::Boss1() :
	atack_pattern(0)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(150, 150);							//当たり判定の大きさ
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

	hp = 100.0f;
}

Boss1::~Boss1()
{
}

void Boss1::Initialize()
{
	//画像読み込み
	image = LoadGraph("Resource/Images/enemy/ship3.png");
}

void Boss1::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//時間経過
	shot_timer += delta_seconds;

	EnemyShot* shot;
	EnemyBase* enemy;

	if (shot_timer >= 0.5f)
	{

		switch (atack_pattern)
		{
		case 0:
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(location.x, location.y));
			shot->SetShotType(eEnemy1);
			atack_pattern = 1;
			break;
		case 1:
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(location.x, location.y + 150));
			shot->SetShotType(eEnemy1);
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(location.x, location.y - 150));
			shot->SetShotType(eEnemy1);
			atack_pattern = 2;
			break;
		case 2:
			object_manager->CreateGameObject<Enemy3>(Vector2D(location.x, location.y + 150));
			object_manager->CreateGameObject<Enemy3>(Vector2D(location.x, location.y - 150));
			atack_pattern = 0;
			break;
		default:
			break;
		}

		//タイマーリセット
		shot_timer = 0.0f;
	}

}

void Boss1::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 10.0f, 0.0f, image, TRUE);
	}
}

void Boss1::Finalize()
{
}

void Boss1::OnHitCollision(GameObject* hit_object)
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
		hp -= player_stats.attack_power / 4;
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}

	if (hp <= 0.0f)
	{
		object_manager->CreateGameObject< ExperiencePoints>(this->location);
		object_manager->DestroyGameObject(this);
	}
}

void Boss1::Movement(float delta_seconds)
{
	float speed = 200.0f;

	location += velocity * speed * delta_seconds;
}

void Boss1::Animation()
{
}
