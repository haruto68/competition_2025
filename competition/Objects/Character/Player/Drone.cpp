#include "Drone.h"
#include "UserTemplate.h"

Drone::Drone()
{

	ResourceManager* rm = ResourceManager::GetInstance();
	// ���W
	location = player_location;
	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(15, 15);
	//collision.object_type = eObjectType::eDrone;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eEnemyShot);
	// �摜�ݒ�
	// ���C���[�ݒ�
	z_layer = 2;
	// �����ݒ�
	is_mobility = true;
	// �����擾

}

Drone::~Drone()
{

}

void Drone::Initialize()
{
	//�摜�ǂݍ���
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