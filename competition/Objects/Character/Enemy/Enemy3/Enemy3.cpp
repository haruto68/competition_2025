#include "Enemy3.h"

Enemy3::Enemy3() 
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(20, 20);							//�����蔻��̑傫��
	collision.object_type = eObjectType::eEnemy;					//�I�u�W�F�N�g�̃^�C�v
	collision.hit_object_type.push_back(eObjectType::ePlayer);		//�Ԃ���I�u�W�F�N�g�̃^�C�v
	collision.hit_object_type.push_back(eObjectType::ePlayerShot);	//�Ԃ���I�u�W�F�N�g�̃^�C�v
	// �����X�s�[�h
	// speed=200.0f;
	// �摜�ݒ�
	// ���C���[�ݒ�
	z_layer = 2;
	// �����ݒ�
	is_mobility = true;

}

Enemy3::~Enemy3()
{
}

void Enemy3::Initialize()
{
	
	/*speed = 200.0f;*/
}

void Enemy3::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();
}

void Enemy3::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	// ��(�����l�p��`�悷��)
	Vector2D t1 = location - (collision.box_size / 2.0f);
	Vector2D br = location + (collision.box_size / 2.0f);
	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 255, 255), TRUE);
	DrawString(t1.x, t1.y, "Enemy1", GetColor(0, 0, 0), TRUE);
}

void Enemy3::Finalize()
{
	
}

void Enemy3::OnHitCollision(GameObject*)
{
}

void Enemy3::Movement(float delta_seconds)
{
	float speed = 200.0f;
	/*location.x -= 1.0f * speed * delta_seconds;*/
	location.x -= 1.0f * speed * delta_seconds;
	if (location.x <= 640 || location.x >= 1280)
	{
		speed *= -1;

	}
}



void Enemy3::Animation()
{
}
