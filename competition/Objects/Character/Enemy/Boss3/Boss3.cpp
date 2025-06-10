#include "Boss3.h"

Boss3::Boss3()
{
	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(150, 150);						//�����蔻��̑傫��
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

	//�ő�HP�ݒ�
	max_hp = 650;
	hp = float(max_hp);

	//�摜�ǂݍ���
	image = rm->GetImages("Resource/Images/enemy/ship3_col3.png")[0];
}

Boss3::~Boss3()
{
}

void Boss3::Initialize()
{
	int random = rand() % 2;
	if (random == 0)
		velocity.y = -0.7f;
	else
		velocity.y = 0.7f;


}

void Boss3::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	//HP�����v�Z
	ratio = (hp * 100) / max_hp;
	if (ratio <= 0)
	{
		ratio = 0;
	}

	//���Ԍo��
	shot_timer += delta_seconds;

	EnemyShot* shot;

	//�U��
	if (hp > 0 && shot_timer >= 0.6f)
	{
		switch (atack_pattern)
		{
		case 0:
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1280 + 640, location.y));
			shot->SetShotType(eEnemy15);
			atack_pattern = 1;
			break;
		case 1:
			atack_pattern = 2;
			break;
		case 2:
			atack_pattern = 3;
			break;
		case 3:
			atack_pattern = 4;
			break;
		case 4:
			atack_pattern = 0;
			break;
		default:
			break;
		}

		//�^�C�}�[���Z�b�g
		shot_timer = 0.0f;
	}

	//��
	if (hp <= 0.0f)
	{
		collision.is_blocking = false;
		death_count -= (delta_seconds * 1.0f);
		transparency--;
	}
	if (death_count <= 0.0)
	{
		death_flag = true;
	}

}

void Boss3::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	if (image != -1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
		DrawRotaGraphF(location.x, location.y, 10.0f, 0.0f, image, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	// ���݂�HP�̃o�[�̕`��
	if (ratio != 0)
	{
		DrawRotaGraph(100, 670, 1.0, 0, hp_bar1, 1, 0);
	}
	for (int i = 0; i < ratio; i++)
	{
		DrawRotaGraph((105 + (i * 11)), 670, 1.0, 0, hp_bar2, 1, 0);
	}
	if (ratio != 0)
	{
		SetFontSize(26);
		DrawFormatString(7, 657, GetColor(255, 0, 255), "BOSS");
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Boss3::Finalize()
{
}

void Boss3::OnHitCollision(GameObject* hit_object)
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
		hp -= player_stats.attack_power / 2;
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}
}

void Boss3::Movement(float delta_seconds)
{
	float speed = 200.0f;

	if ((location.y + velocity.y) <= (65.0f + collision.box_size.y) || (location.y + velocity.y) >= (680 - collision.box_size.y))
	{

		if (velocity.y < 0)
			velocity.y = 0.7f;
		else
			velocity.y = -0.7f;
	}

	location += velocity * speed * delta_seconds;
}

void Boss3::Animation()
{
}

int Boss3::GetBoss3Hp()
{
	return ratio;
}

float Boss3::GetBoss3DeathCount()
{
	return death_count;
}

bool Boss3::GetDeathFlag()
{
	return death_flag;
}