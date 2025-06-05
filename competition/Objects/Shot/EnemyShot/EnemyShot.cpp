#include"EnemyShot.h"
#include"../../../Utility/InputManager.h"

EnemyShot::EnemyShot() :
	screen_velocity(0.0),
	shot_image(),
	birth_count(800),
	old_velocity(0.0f)
{

	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// ���W
	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(10, 10);
	collision.object_type = eObjectType::eEnemyShot;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	// �摜�ݒ�
	// ���C���[�ݒ�
	z_layer = 3;
	// �����ݒ�
	is_mobility = true;

	//�摜�ǂݍ���
	shot_image[0] = rm->GetImages("Resource/Images/enemy_shot/shot1.png")[0];
	shot_image[1] = rm->GetImages("Resource/Images/enemy_shot/shot2.png")[0];
	shot_image[2] = rm->GetImages("Resource/Images/enemy_shot/shot3.png")[0];
	
}

EnemyShot::~EnemyShot()
{

}

void EnemyShot::Initialize()
{
	turn_target[0] = Vector2D(location.x - 1200, location.y);
	turn_target[1] = Vector2D(location.x - 1200, location.y - 200);
	turn_target[2] = Vector2D(location.x - 1200, location.y + 200);
	turn_target[3] = Vector2D(location.x - 600, location.y);
	turn_target[4] = Vector2D(location.x - 600, location.y);
}

void EnemyShot::Update(float delta_seconds)
{
	Movement(delta_seconds);

	Animation();
}

void EnemyShot::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);

	int image = -1;

	switch (shot_type)
	{
	case eEnemy1:
		image = shot_image[0];
		break;
	case eEnemy2:
		image = shot_image[2];
		break;
	case eEnemy3:
		image = shot_image[2];
		break;
	case eEnemy4:
		image = shot_image[1];
		break;
	case eEnemy5:
		image = shot_image[1];
		break;
	default:
		image = shot_image[1];
		break;
	}

	if (image != -1)
	{
		DrawRotaGraph(location.x, location.y, 1.5, 0, image,TRUE);
	}
	
}

void EnemyShot::Finalize()
{

}

void EnemyShot::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	switch (type)
	{
	case eNone:
		break;
	case ePlayer:
		object_manager->DestroyGameObject(this);
		break;
	case eEnemy:
		break;
	case ePlayerShot:
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}
}

Vector2D EnemyShot::GetScreenVelocity()
{
	Vector2D value = 0.0f;
	value.x = screen_velocity;
	screen_velocity = 0.0f;
	return value;
}

Vector2D EnemyShot::GetVelocity()
{
	return this->velocity;
}

void EnemyShot::SetVelocity(Vector2D velocity)
{
	this->velocity += velocity;
}

void EnemyShot::Movement(float delta_seconds)
{
	// �ړ��X�s�[�h
	float speed = 200.0f;
	// �ړ�����
	Vector2D direction = 0.0f;

	switch (shot_type)
	{
	case eEnemy1:	//�^��
		velocity.x = -1.0f;
		break;
	case eEnemy2:	//�^��
		velocity.y = -1.0f;
		break;
	case eEnemy3:	//�^��
		velocity.y = 1.0f;
		break;
	case eEnemy4:	//���@�_��
		if(location.x > old_player_location.x)
		{
			velocity = Tracking(location, old_player_location);
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy5:	//���@��_��(75.0f)
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y - 75.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy6:	//���@���_��(75.0f)
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y + 75.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy7:	//�ォ�牺�ɃJ�[�u
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y)) * 2;
			velocity.y -= 1.0f;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy8:	//�������ɃJ�[�u
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y)) * 2;
			velocity.y += 1.0f;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy9:	//�O�l�O�l
		velocity.x = -1.0f;
		//
		if (turn_flag[1])
			velocity.y += 0.01f;
		else
			velocity.y -= 0.01f;
		//
		if (velocity.y > 1.0f)
			turn_flag[1] = false;
		else if (velocity.y < -1.0f)
			turn_flag[1] = true;
		break;
	case eEnemy10:
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y - 150.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy11:
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y + 150.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy12:
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y - 225.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	case eEnemy13:
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, Vector2D(old_player_location.x, old_player_location.y + 225.0f)) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
			break;
	case eEnemy14:	//���@�_��
		if (location.x > old_player_location.x)
		{
			velocity = Tracking(location, old_player_location) * 2;
			old_velocity = velocity;
		}
		else
			velocity = old_velocity;
		break;
	default:
		break;
	}

	
	//�ʒu���W�������x�����炷
	location += velocity * speed * delta_seconds;

}

void EnemyShot::Animation()
{

}