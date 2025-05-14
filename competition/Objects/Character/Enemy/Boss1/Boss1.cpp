#include "Boss1.h"

Boss1::Boss1()
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
}

Boss1::~Boss1()
{
}

void Boss1::Initialize()
{
	velocity.y = -1.0f;
	velocity.x = -0.5f;

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

	if (shot_timer >= shot_cooldown)
	{
		EnemyShot* shot = object_manager->CreateGameObject<EnemyShot>(this->location);
		shot->SetShotType(eEnemy1);

		//タイマーリセット
		shot_timer = 0.0f;
	}
}

void Boss1::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, 0.0f, image, TRUE);
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
		object_manager->CreateGameObject< ExperiencePoints>(this->location);
		object_manager->DestroyGameObject(this);
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}
}

void Boss1::Movement(float delta_seconds)
{
	float speed = 200.0f;

	if (location.y <= 95.0f)
	{
		velocity.y = 1.0f;
	}

	if ((location.y + velocity.y) <= collision.box_size.y || (location.y + velocity.y) >= (680 - collision.box_size.y))
	{

		if (velocity.y < 0)
			velocity.y = 1.0f;
		else
			velocity.y = -1.0f;
	}

	location += velocity * speed * delta_seconds;
}

void Boss1::Animation()
{
}
