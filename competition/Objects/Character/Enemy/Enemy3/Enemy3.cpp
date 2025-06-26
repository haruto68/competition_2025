#include "Enemy3.h"

Enemy3::Enemy3() 
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

	exp_num = 1;
}

Enemy3::~Enemy3()
{
}

void Enemy3::Initialize()
{
	
	speed = 200.0f;

	hp = 3.0;
}

void Enemy3::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();
}

void Enemy3::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, radian + (-velocity.y / 2), image, TRUE);
	}
}

void Enemy3::Finalize()
{
}

void Enemy3::OnHitCollision(GameObject* hit_object)
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

void Enemy3::Movement(float delta_seconds)
{

	if (location.x > old_player_location.x)
	{
		velocity = Tracking(location, old_player_location)*2;
		old_velocity = velocity;
	}
	else
		velocity = old_velocity;

	location += velocity * speed * delta_seconds;
}



void Enemy3::Animation()
{
}
