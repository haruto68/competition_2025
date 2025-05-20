#include "Enemy4.h"

Enemy4::Enemy4()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(30, 30);							//�����蔻��̑傫��
	collision.object_type = eObjectType::eEnemy;					//�I�u�W�F�N�g�̃^�C�v
	collision.hit_object_type.push_back(eObjectType::ePlayer);		//�Ԃ���I�u�W�F�N�g�̃^�C�v
	collision.hit_object_type.push_back(eObjectType::ePlayerShot);	//�Ԃ���I�u�W�F�N�g�̃^�C�v

	// �摜�ݒ�
	// ���C���[�ݒ�
	z_layer = 2;
	// �����ݒ�
	is_mobility = true;

}

Enemy4::~Enemy4()
{
}

void Enemy4::Initialize()
{

	speed = 2.0f;

	//�摜�ǂݍ���
	image = LoadGraph("Resource/Images/enemy/ship.png");

	hp = 3.0;

	location = Vector2D(1300, 600);

	point.clear();
	point.push_back(Vector2D(200, 600));  //����
	point.push_back(Vector2D(1200, 200));  //�E��
	point.push_back(Vector2D(-100, 200));  //����

	timar = 0.0f;
	spawn_index = 0;
}

void Enemy4::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();


	//if (is_first_Enemy && spawn_index < 2)
	//{
	//	timar += delta_seconds;

	//	if (timar >= 0.5f)
	//	{
	//		timar = 0.0f;
	//		spawn_index++;

	//		//���炵�ďo��
	//		Vector2D spawn_offset(30.0f * spawn_index, 0.0f);
	//		Enemy4 new_enemy = object_manager->
	//	}
	//}
}

void Enemy4::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	/*if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, radian + (-velocity.y / 2), image, TRUE);
	}*/

	 //��(�����l�p��`�悷��)
	Vector2D t1 = location - (collision.box_size / 2.0f);
	Vector2D br = location + (collision.box_size / 2.0f);
	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 255, 255), TRUE);
	DrawString(t1.x, t1.y, "3", GetColor(0, 0, 0), TRUE);
}

void Enemy4::Finalize()
{

}

void Enemy4::OnHitCollision(GameObject* hit_object)
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
	if (hp <= 0.0)
	{
		object_manager->CreateGameObject< ExperiencePoints>(this->location);
		object_manager->DestroyGameObject(this);
	}
}

void Enemy4::Movement(float delta_seconds)
{
	if (move_point >= point.size())
		return;

	Vector2D taget = point[move_point];
	Vector2D direction = taget - location;

	if (direction.Length() < 5.0f)
	{
		move_point++;
		return;
	}

	direction.Normalize();
	velocity = direction;
	/*if (location.x > old_player_location.x)
	{
		velocity = Tracking(location, old_player_location) * 2;
		old_velocity = velocity;
	}
	else
		velocity = old_velocity;*/

	location += velocity * speed * delta_seconds;
}



void Enemy4::Animation()
{
}

void Enemy4::setClone()
{
}

