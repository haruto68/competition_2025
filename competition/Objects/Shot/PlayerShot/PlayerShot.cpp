#include"PlayerShot.h"
#include"../../../Utility/InputManager.h"

PlayerShot::PlayerShot() :
	screen_velocity(0.0f)
{

	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// ���W
	location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);
	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(0, 0);
	collision.object_type = eObjectType::ePlayerShot;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	// �摜�ݒ�
	// ���C���[�ݒ�
	z_layer = 2;
	// �����ݒ�
	is_mobility = true;

}

PlayerShot::~PlayerShot()
{

}

void PlayerShot::Initialize()
{

}

void PlayerShot::Update(float delta_seconds)
{
	Movement(delta_seconds);

	Animation();
}

void PlayerShot::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);

	DrawBox(location.x - 15, location.y - 15, location.x + 15, location.y + 15, GetColor(0, 255, 255), TRUE);

}

void PlayerShot::Finalize()
{

}

void PlayerShot::OnHitCollision(GameObject* hit_object)
{

}

Vector2D PlayerShot::GetScreenVelocity()
{
	Vector2D value = 0.0f;
	value.x = screen_velocity;
	screen_velocity = 0.0f;
	return value;
}

Vector2D PlayerShot::GetVelocity()
{
	return this->velocity;
}

void PlayerShot::SetVelocity(Vector2D velocity)
{
	this->velocity += velocity;
}

void PlayerShot::Movement(float delta_seconds)
{
	// �ړ��X�s�[�h
	float speed = 200.0f;
	// �ړ�����
	float direction = 0.0f;

	// ���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//G�L�[�Œe�𔭎˂���
	if (input->GetKey(KEY_INPUT_G))
	{
		direction = 1.0f;
		flip_flag = FALSE;
	}

	//�ړ������ɂ���āAX���W�̈ړ��ʂ̉������s��
	if (direction != 0.0f)
	{
		velocity.x += 0.5 * direction;
	}

	//�ʒu���W�������x�����炷
	while ((location.x + velocity.x) <= (D_WIN_MAX_X)-(collision.box_size.x / 2.0f))
	{
		location += velocity * speed * delta_seconds;
	}
}

void PlayerShot::Animation()
{

}