#include "Enemy2.h"

Enemy2::Enemy2()
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

Enemy2::~Enemy2()
{
}

void Enemy2::Initialize()
{
	//�@���G2�̃T�C�Y(�傫��)
	collision.box_size = Vector2D(20.0f, 20.0f);
	//box_size = Vector2D(20.0fs, 20.0f);
	// ���e�L�̑���
	speed = 200.0f;

	//�摜�ǂݍ���
	image = LoadGraph("Resource/Images/enemy/cannon.png");

	hp = 2.0;
}

void Enemy2::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	//���Ԍo��
	shot_timer += delta_seconds;

	if (shot_timer >= shot_cooldown)
	{
		EnemyShot* shot = object_manager->CreateGameObject<EnemyShot>(this->location);
		shot->SetShotType(eEnemy3);

		//�^�C�}�[���Z�b�g
		shot_timer = 0.0f;
	}
}

void Enemy2::Draw(const Vector2D&, bool) const
{
	
	if (image != -1)
	{
		float angle;
		if (trans == false)
		{
			angle = 0.0f;
		}
		else
		{
			angle = 3.14 / 1.0f;
		}
		DrawRotaGraphF(location.x, location.y, 1.0f, angle, image, TRUE);
	}
	

	//// ��(�����l�p��`�悷��)
	//Vector2D t1 = location - (collision.box_size / 2.0f);
	//Vector2D br = location + (collision.box_size / 2.0f);
	//// �F�̎l�p��`��
	//DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(0, 255, 255), TRUE);
	//SetFontSize(15);
	//DrawString(location.x,location.y, "2", GetColor(0, 0, 0), TRUE);
}

void Enemy2::Finalize()
{
}

void Enemy2::OnHitCollision(GameObject* hit_object)
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
		hp -= 1.0/4;
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

void Enemy2::Movement(float delta_seconds)
{
	//���ɓ�����
	velocity.x = -1.0f;
	
	location += velocity * speed * delta_seconds;
}

void Enemy2::Animation()
{
}

void Enemy2::SetTrans()
{
	trans = true;
}
