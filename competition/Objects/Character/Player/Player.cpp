#include"Player.h"
#include"../../../Utility/InputManager.h"
#include"UserTemplate.h"

Player::Player() : 
	screen_velocity(0.0f)
{

	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// ���W
	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(0, 0);
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eEnemyShot);
	collision.hit_object_type.push_back(eObjectType::eItem);
	// �摜�ݒ�
	// ���C���[�ݒ�
	z_layer = 2;
	// �����ݒ�
	is_mobility = true;

}

Player::~Player()
{

}

void Player::Initialize()
{

}

void Player::Update(float delta_seconds)
{
	Movement(delta_seconds);

	Animation();
}

void Player::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);
}

void Player::Finalize()
{

}

void Player::OnHitCollision(GameObject* hit_object)
{

}

Vector2D Player::GetScreenVelocity()
{
	Vector2D value = 0.0f;
	value.x = screen_velocity;
	screen_velocity = 0.0f;
	return value;
}

Vector2D Player::GetVelocity()
{
	return this->velocity;
}

void Player::SetVelocity(Vector2D velocity)
{
	this->velocity += velocity;
}

void Player::Movement(float delta_seconds)
{
	// �ړ��X�s�[�h
	float speed = 200.0f;
	// �ړ�����
	float direction = 0.0f;

	// ���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();
}

void Player::Animation()
{

}