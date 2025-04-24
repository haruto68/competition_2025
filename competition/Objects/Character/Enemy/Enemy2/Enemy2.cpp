#include "Enemy2.h"

Enemy2::Enemy2()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(20, 20);							//�����蔻��̑傫��
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
	//box_size = Vector2D(20.0f, 20.0f);
	// ���e�L�̑���
	speed = 200.0f;

	//�摜�ǂݍ���
	LoadGraph("Resouce/Images/enemy/cannon.png");
}

void Enemy2::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();
}

void Enemy2::Draw(const Vector2D&, bool) const
{

	DrawRotaGraphF(location.x, location.y, 1.0f, 0.0f, image, TRUE);

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
}

void Enemy2::Movement(float delta_seconds)
{

	location += velocity * speed * delta_seconds;
}

void Enemy2::Animation()
{
}
