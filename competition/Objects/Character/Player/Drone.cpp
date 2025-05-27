#include "Drone.h"
#include "UserTemplate.h"

Drone::Drone()
{

	ResourceManager* rm = ResourceManager::GetInstance();
	// 座標
	location = player_location;
	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(15, 15);
	//collision.object_type = eObjectType::eDrone;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eEnemyShot);
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;
	// 音源取得

}

Drone::~Drone()
{

}

void Drone::Initialize()
{
	//画像読み込み
	//image = LoadGraph("Resource/Images/player/player.png");
}

void Drone::Update(float delta_seconds)
{
	
}

void Drone::Draw(const Vector2D& screen_offset, bool flip_flag) const
{

}

void Drone::Finalize()
{

}

void Drone::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	switch (type)
	{
	case eNone:
		break;
	case ePlayer:
		break;
	case eEnemy:
		object_manager->DestroyGameObject(this);
		break;
	case ePlayerShot:
		break;
	case eEnemyShot:
		object_manager->DestroyGameObject(this);
		break;
	case eItem:
		break;
	default:
		break;
	}

}