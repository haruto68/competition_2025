#include "Enemy8.h"

Enemy8::Enemy8() :
	target(0),
	turn_flag(false),
	vel2(0.0f)
{

	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(30, 30);							//�����蔻��̑傫��
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

	//�����擾(0: �G���j�󎞂̉� 1: �G���e�����������̉�)
	soundseffect[0] = rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemybreak.mp3");
	soundseffect[1] = rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemyshot.mp3");
	soundseffect[2] = rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemy_dead_se.mp3");
	ChangeVolumeSoundMem(sound_volume[0], soundseffect[0]);
	ChangeVolumeSoundMem(sound_volume[1], soundseffect[1]);
	ChangeVolumeSoundMem(sound_volume[2], soundseffect[2]);

	image = rm->GetImages("Resource/Images/enemy/ship23.png")[0];

	exp_num = 3;
}

Enemy8::~Enemy8()
{

}


void Enemy8::Initialize()
{
	//velocity.x = -1.0f;

	hp = 17.0f;
}

void Enemy8::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	EnemyShot* shot;
	//���Ԍo��
	shot_timer += delta_seconds;
	shot_cooldown = 1.0f;

	if (shot_timer >= shot_cooldown)
	{
		if (target == 0)
		{
			shot = object_manager->CreateGameObject<EnemyShot>(this->location);
			shot->SetShotType(eEnemy7);
			target = 1;
		}
		else
		{
			shot = object_manager->CreateGameObject<EnemyShot>(this->location);
			shot->SetShotType(eEnemy8);
			target = 0;
		}
		PlaySoundMem(soundseffect[1], DX_PLAYTYPE_BACK, TRUE);

		//�^�C�}�[���Z�b�g
		shot_timer = 0.0f;
	}

}

void Enemy8::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	if (image != -1)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, 0.0f, image, TRUE);
	}
}

void Enemy8::Finalize()
{

}

void Enemy8::OnHitCollision(GameObject* hit_object)
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
		PlaySoundMem(soundseffect[0], DX_PLAYTYPE_BACK, TRUE);
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}
}

void Enemy8::Movement(float delta_seconds)
{
	float speed = 200.0f;

	//
	if (turn_flag)
		velocity.x += 0.01f;
	else
		velocity.x -= 0.01f;
	//
	if (velocity.x > 1.5f)
		turn_flag = false;
	else if (velocity.x < -1.5f)
		turn_flag = true;

	location += velocity * speed * delta_seconds;
	location.x -= 0.05f;
}

void Enemy8::Animation()
{

}