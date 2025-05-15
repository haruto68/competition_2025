#include"Player.h"
#include"../../../Utility/InputManager.h"
#include"UserTemplate.h"


Player::Player() : 
	screen_velocity(0.0f),
	shot_timer(0.0f),
	SHOT_INTERVAL(0.3f),
	threeway_flag(false),
	is_invincible(false),
	invincible_timer(0.0f)
{

	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// ���W
	location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);
	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(35, 40);
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
	//�摜�ǂݍ���
	image = LoadGraph("Resource/Images/player/player.png");
}

void Player::Update(float delta_seconds)
{
	Movement(delta_seconds);

	Animation();

	// ���G��Ԃ̍X�V
	if (is_invincible)
	{
		invincible_timer -= delta_seconds;
		if (invincible_timer <= 0.0f)
		{
			is_invincible = false;
		}
	}

	if (shot_timer > 0.0f)
	{
		shot_timer -= delta_seconds;
	}

	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	if ((InputManager::GetInstance()->GetButton(13) || CheckHitKey(KEY_INPUT_B)) && shot_timer <= 0.0f)
	{
		PlayerShot* shot = object_manager->CreateGameObject<PlayerShot>(this->location);
		shot->SetShotType(ePlayer1);
		shot->SetPlayerStats(this->GetPlayerStats());

		if (threeway_flag == true)
		{
			PlayerShot* angled_shot_up = object_manager->CreateGameObject<PlayerShot>(this->location);
			angled_shot_up->SetShotType(ePlayer1);
			angled_shot_up->SetPlayerStats(this->GetPlayerStats());
			angled_shot_up->SetAngle(10.0f);

			PlayerShot* angled_shot_down = object_manager->CreateGameObject<PlayerShot>(this->location);
			angled_shot_down->SetShotType(ePlayer1);
			angled_shot_down->SetPlayerStats(this->GetPlayerStats());
			angled_shot_down->SetAngle(-10.0f);
		}

		shot_timer = SHOT_INTERVAL;
	}
}

void Player::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);

	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 2.0f, 0.0f, image, TRUE);
	}

	//DrawBox(location.x - 10, location.y - 10, location.x + 10, location.y + 10, GetColor(255, 0, 0), TRUE);
	SetFontSize(20);
	DrawFormatString(5, 50, GetColor(255, 255, 255), "���݂̃v���C���[���x���F%d", player_stats.player_level);
	DrawFormatString(5, 70, GetColor(255, 255, 255), "�ݐσv���C���[���x���F%d", player_stats.current_exp);
	DrawFormatString(5, 90, GetColor(255, 255, 255), "���̃��x���A�b�v�ɕK�v��EXP�F%d", player_stats.next_level_exp);
}

void Player::Finalize()
{

}

void Player::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	switch (type)
	{
	case eNone:
		break;
	case eEnemy:
		if (is_invincible)
		{
			return;
		}

		player_stats.life_count -= 1.0f;
		is_invincible = true;
		invincible_timer = 1.0f;
		break;
	case ePlayerShot:
		break;
	case eEnemyShot:
		if (is_invincible)
		{
			return;
		}

		player_stats.life_count -= 1.0f;
		is_invincible = true;
		invincible_timer = 1.0f;
		break;
	case eItem:
		AddExperience(5);
		break;
	default:
		break;
	}
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
	float speed = 200.0 + player_stats.move_speed;
	// �ړ�����
	Vector2D direction = 0.0f;
	// ����
	float slow = 0.005f;//����
	slow = 1.0f;//����Ȃ�

	// ���͊Ǘ��C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();
	Vector2D leftstick = InputManager::GetInstance()->GetLeftStick();

	//���͏�Ԃɂ���Ĉړ�������ύX����
	if (leftstick.y > 0.5f || input->GetKey(KEY_INPUT_UP) || input->GetKey(KEY_INPUT_W))		//��ړ�
	{
		direction.y = -1.0f;
		flip_flag = FALSE;
	}
	if (leftstick.y < -0.5f || input->GetKey(KEY_INPUT_DOWN) || input->GetKey(KEY_INPUT_S))	//���ړ�
	{
		direction.y = 1.0f;
		flip_flag = FALSE;
	}
	if (leftstick.x < -0.5f || input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A))	//���ړ�
	{
		direction.x = -1.0f;
		flip_flag = FALSE;
	}
	if (leftstick.x > 0.5f || input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D))	//�E�ړ�
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
	if ((location.y + velocity.y) < (120) - (collision.box_size.y / 2.0f))
	{
		if ((location.y + velocity.y) < location.y)
		{
			velocity.y = 0.0f;
		}
	}
	//����ʒ[
	if ((location.y + velocity.y) >= (680) - (collision.box_size.y / 2.0f))
	{
		if ((location.y + velocity.y) > location.y)
		{
			velocity.y = 0.0f;
		}
	}


	//�ʒu���W�������x�����炷
	location += velocity * speed * delta_seconds;
}

void Player::Animation()
{

}

void Player::AddExperience(float exp)
{
	player_stats.current_exp += exp;

	// ���x���A�b�v�`�F�b�N
	while (player_stats.current_exp >= player_stats.next_level_exp)
	{
		player_stats.current_exp -= player_stats.next_level_exp;
		LevelUp();
	}
}

void Player::LevelUp()
{	
	player_stats.player_level++;			//�v���C���[���x���A�b�v
	player_stats.next_level_exp += 50;		//���̃��x���A�b�v�ɕK�v�Ȍo���l�ʂ̑���
}

void Player::StatsUp(ePowerUp powerup)
{
	switch (powerup)
	{
	case ePowerUp::eHp:
		if(player_stats.life_count < player_stats.player_hp_max)
		player_stats.life_count += 1.0f;		// HP�c�ʃA�b�v
		break;
	case ePowerUp::eDamage:
		player_stats.attack_power += 1.0f;		// �U���̓A�b�v
		break;
	case ePowerUp::eSpeed:
		player_stats.move_speed = Max(100.0f, player_stats.move_speed + 5.0f);		// �ړ����x�A�b�v
		break;
	case ePowerUp::eShotspeed:
		SHOT_INTERVAL = Max(0.1f, SHOT_INTERVAL - 0.02f);  // ������0.02�b�ɐ���
		break;
	case ePowerUp::eThreeway:
		threeway_flag = true;
	default:
		break;
	}
}