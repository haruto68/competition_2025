#include"DxLib.h"
#include"GameObject.h"
#include"GameObjectManager.h"

#include"Item/ExperiencePoints/ExperiencePoints.h"

GameObject::GameObject() :
	location(0.0f),
	death_location(0.0f),
	exp_num(0),
	hp(1.0f),
	speed(0),
	image(NULL),
	transparency(255),
	z_layer(0),
	is_mobility(false),
	player_location(0.0f),
	player_stats(),
	object_manager(nullptr),
	explosions(),
	death_timer(0),
	anim_num(0),
	explosion_flag(false)
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	explosions[0] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion1.png")[0];
	explosions[1] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion2.png")[0];
	explosions[2] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion3.png")[0];
	explosions[3] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion4.png")[0];
	explosions[4] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion5.png")[0];
	explosions[5] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion6.png")[0];
	explosions[6] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion7.png")[0];
	explosions[7] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion8.png")[0];
	explosions[8] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion9.png")[0];
	explosions[9] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion10.png")[0];
	explosions[10] = rm->GetImages("Resource/Images/GameMaker/Effects/Explosion/Explosion11.png")[0];
	explosions[11] = 0;
}

GameObject::~GameObject()
{

}

/// <summary>
/// ����������
/// </summary>
void GameObject::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void GameObject::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void GameObject::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	if(!explosion_flag)
	{
		// �I�t�Z�b�g�l����ɉ摜�̕`����s��
		Vector2D graph_location = this->location + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, image, TRUE, flip_flag);
	}
}

/// <summary>
/// �I��������
/// </summary>
void GameObject::Finalize()
{

}

//�����蔻��ʒm����
void GameObject::OnHitCollision(GameObject* hit_object)
{

}

float GameObject::GetHp()
{
	return this->hp;
}
void GameObject::SetHp(float h)
{
	this->hp = h;
}

//���W�擾����
const Vector2D& GameObject::GetLocation() const
{
	return location;
}

//���W�ݒ菈��
void GameObject::SetLocation(const Vector2D location)
{
	this->location = location;
}

//�R���W�����擾����
const Collision& GameObject::GetCollision() const
{
	return collision;
}

//���C���[�擾����
const unsigned char GameObject::GetZLayer() const
{
	return z_layer;
}

//�����擾����
const bool GameObject::GetMobility() const
{
	return is_mobility;
}

//���S���W�ݒ菈��
void GameObject::SetDeathLocation()
{
	this->death_location = location;
}

//���S���W�Œ菈��
void GameObject::KeepDeathLocation()
{
	this->explosion_flag = true;
	collision.is_blocking = false;
	location = this->death_location;
}

//�v���C���[���W�ݒ菈��
void GameObject::SetPlayerLocation(Vector2D location)
{
	if (player_location.x == 0.0f && player_location.y == 0.0f)
	{
		old_player_location = location;
	}
	player_location = location;
}

//�v���C���[�X�e�[�^�X�ݒ菈��
void GameObject::SetPlayerStats(PlayerStats stats)
{
	player_stats = stats;
}


//A��B��ǔ����鏈��
Vector2D GameObject::Tracking(Vector2D A, Vector2D B)
{
	Vector2D velocity;	//�����x
	float distance;		//����

	velocity.x = A.x - B.x;
	velocity.y = A.y - B.y;

	distance = sqrt(pow(velocity.x, 2.0) + pow(velocity.y, 2.0));

	velocity.x /= distance;
	velocity.y /= distance;

	velocity *= -1;

	return velocity;

}

//�C���X�^���X�m�F����
const GameObjectManager* GameObject::CheckInstance() const
{
	return object_manager;
}

//�C���X�^���X�ݒ菈��
void GameObject::SetInstance(GameObjectManager* instance)
{
	object_manager = instance;
}

//��������
void GameObject::Explosion(float delta_second)
{
	death_timer += delta_second;

	if (death_timer >= 0.08f)
	{
		death_timer = 0.0f;

		if (anim_num < 10)
		{
			anim_num += 1;
		}
		else
		{
			for (int i = 0; i < exp_num; i++)
			{
				Vector2D loc = death_location;
				loc.x += rand() % 80 - 40;
				loc.y += rand() % 80 - 40;
				object_manager->CreateGameObject<ExperiencePoints>(loc);
			}

			object_manager->DestroyGameObject(this);
		}
	}
}

//�����t���O�擾����
bool GameObject::GetExplosionFlag()
{
	return this->explosion_flag;
}

//�����`��
void GameObject::DrawExplosion() const
{
	DrawRotaGraphF(death_location.x, death_location.y, 0.5, 0.0, explosions[anim_num], TRUE, false);
}