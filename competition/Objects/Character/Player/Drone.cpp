#include "Drone.h"
#include "UserTemplate.h"

Drone::Drone() : rotation_angle(0.0f)
{

	ResourceManager* rm = ResourceManager::GetInstance();
	// ���W
	location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);
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
	rotation_angle += 1.0f * delta_seconds; // ��: ���t���[��1���W�A����]
	if (rotation_angle > 360.0f)
	{
		rotation_angle -= 360.0f;
	}
}

void Drone::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);
	DrawBox(location.x - 10, location.y - 10, location.x + 10, location.y + 10, GetColor(255, 0, 0), TRUE);}

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