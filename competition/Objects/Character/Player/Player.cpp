#include"Player.h"
#include"../../../Utility/InputManager.h"
#include"UserTemplate.h"


Player::Player() : 
	screen_velocity(0.0f)
{

	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// ���W
	location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);
	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(20, 20);
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

	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyDown(KEY_INPUT_B))
	{
		Shot* shot = object_manager->CreateGameObject<PlayerShot>(this->location);
		shot->SetShotType(ePlayer1);
	}
}

void Player::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);

	DrawBox(location.x - 10, location.y - 10, location.x + 10, location.y + 10, GetColor(255, 0, 0), TRUE);
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
	Vector2D direction = 0.0f;
	// ����
	float slow = 0.005f;

	// ���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();


	//���͏�Ԃɂ���Ĉړ�������ύX����
	if (input->GetKey(KEY_INPUT_UP) || input->GetKey(KEY_INPUT_W))		//��ړ�
	{
		direction.y = -1.0f;
		flip_flag = FALSE;
	}
	if (input->GetKey(KEY_INPUT_DOWN) || input->GetKey(KEY_INPUT_S))	//���ړ�
	{
		direction.y = 1.0f;
		flip_flag = FALSE;
	}
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A))	//���ړ�
	{
		direction.x = -1.0f;
		flip_flag = FALSE;
	}
	if (input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D))	//�E�ړ�
	{
		direction.x = 1.0f;
		flip_flag = FALSE;
	}

	//�ړ������ɂ���āAY���W�̈ړ��ʂ̉������s��
	if (direction.y != 0.0f)
	{
		//�ō����x�𒴂��Ȃ��悤�ɂ���
		float max_speed = Abs<float>((5.0f * 0.5 * direction.y));
		velocity.y += 0.5 * direction.y;
		velocity.y = Min<float>(Max<float>(velocity.y, -max_speed), max_speed);
	}
	else
	{
		//��������
		if (velocity.y < -1e-6f)		//-1e-6f = (0�Ɍ���Ȃ��߂����̒l)
		{
			//��ړ��̌���
			float calc_speed = velocity.y + slow;
			velocity.y = Min<float>(calc_speed, 0.0f);
		}
		else if (velocity.y > 1e-6f)	//1e-6f = (0�Ɍ���Ȃ��߂����̒l)
		{
			//���ړ��̌���
			float cale_spped = velocity.y - slow;
			velocity.y = Max<float>(cale_spped, 0.0f);
		}
	}
	//�ړ������ɂ���āAX���W�̈ړ��ʂ̉������s��
	if (direction.x != 0.0f)
	{
		//�ō����x�𒴂��Ȃ��悤�ɂ���
		float max_speed = Abs<float>((5.0f * 0.5 * direction.x));
		velocity.x += 0.5 * direction.x;
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);
	}
	else
	{
		//��������
		if (velocity.x < -1e-6f)		//-1e-6f = (0�Ɍ���Ȃ��߂����̒l)
		{
			//��ړ��̌���
			float calc_speed = velocity.x + slow;
			velocity.x = Min<float>(calc_speed, 0.0f);
		}
		else if (velocity.x > 1e-6f)	//1e-6f = (0�Ɍ���Ȃ��߂����̒l)
		{
			//���ړ��̌���
			float cale_spped = velocity.x - slow;
			velocity.x = Max<float>(cale_spped, 0.0f);
		}
	}


	//����ʒ[
	if ((location.x + velocity.x) < (collision.box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
	}
	//�E��ʒ[
	if ((location.x + velocity.x) >= (D_WIN_MAX_X) - (collision.box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
	}
	//���ʒ[
	if ((location.y + velocity.y) < (collision.box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
	}
	//����ʒ[
	if ((location.y + velocity.y) >= (D_WIN_MAX_Y)-(collision.box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
	}


	//�ʒu���W�������x�����炷
	location += velocity * speed * delta_seconds;
}

void Player::Animation()
{

}