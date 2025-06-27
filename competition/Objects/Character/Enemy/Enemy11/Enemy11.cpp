#include "Enemy11.h"

Enemy11::Enemy11() :
	old_velocity(),
	target()
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

	image = rm->GetImages("Resource/Images/enemy/ship.png")[0];

	exp_num = 4;
}

Enemy11::~Enemy11()
{
}

void Enemy11::Initialize()
{
	float start = 380;
	if (location.y == start - 200)
		target = Vector2D(-40, start + 200);
	else if (location.y == start - 150)
		target = Vector2D(-40, start + 150);
	else if (location.y == start - 100)
		target = Vector2D(-40, start + 100);
	else if (location.y == start - 50)
		target = Vector2D(-40, start + 50);
	else if (location.y == start)
		target = Vector2D(-40, start);
	else if (location.y == start + 50)
		target = Vector2D(-40, start - 50);
	else if (location.y == start + 100)
		target = Vector2D(-40, start - 100);
	else if (location.y == start + 150)
		target = Vector2D(-40, start - 150);
	else if (location.y == start + 200)
		target = Vector2D(-40, start - 200);

	speed = 400.0f;

	hp = 5.0;
}

void Enemy11::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();
}

void Enemy11::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, radian + (-velocity.y / 2), image, TRUE);
	}
}

void Enemy11::Finalize()
{
}

void Enemy11::OnHitCollision(GameObject* hit_object)
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

void Enemy11::Movement(float delta_seconds)
{

	if (location.x > old_player_location.x)
	{
		velocity = Tracking(location, target) * 2;
		old_velocity = velocity;
	}
	else
		velocity = old_velocity;

	location += velocity * speed * delta_seconds;
}



void Enemy11::Animation()
{
}
