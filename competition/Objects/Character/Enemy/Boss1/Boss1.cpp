#include "Boss1.h"

Boss1::Boss1() : images()
{
	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(120, 260);						//当たり判定の大きさ
	collision.object_type = eObjectType::eEnemy;					//オブジェクトのタイプ
	collision.hit_object_type.push_back(eObjectType::ePlayer);		//ぶつかるオブジェクトのタイプ
	collision.hit_object_type.push_back(eObjectType::ePlayerShot);	//ぶつかるオブジェクトのタイプ
	// 初期スピード
	// speed=200.0f;
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;

	//最大HP設定
	max_hp = 150;
	hp = float(max_hp);

	//画像読み込み
	image = rm->GetImages("Resource/Images/enemy/ship3.png")[0];

	images[0] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/Enemy_Tank_Base.png")[0];
	images[1] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip1_Base.png")[0];
	images[2] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip1_Base_Tilt1.png")[0];
	images[3] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip1_Base_Tilt2.png")[0];
	images[4] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip1_Upgraded.png")[0];
	images[5] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip1_Upgraded_Tilt1.png")[0];
	images[6] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip1_Upgraded_Tilt2.png")[0];

	exp_num = 0;
}

Boss1::~Boss1()
{
}

void Boss1::Initialize()
{
	ChangeVolumeSoundMem(bomb_sound_volume[0], bomb_sound[0]);
	ChangeVolumeSoundMem(bomb_sound_volume[1], bomb_sound[1]);
	ChangeVolumeSoundMem(bomb_sound_volume[2], bomb_sound[2]);
	ChangeVolumeSoundMem(bomb_sound_volume[3], bomb_sound[3]);
}

void Boss1::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

	//HP割合計算
	ratio = (hp * 100) / max_hp;
	if (ratio <= 0)
	{
		ratio = 0;
	}

	//時間経過
	shot_timer += delta_seconds;

	EnemyShot* shot;

	//攻撃
	if (hp > 0 && shot_timer >= 0.5f)
	{
		switch (atack_pattern)
		{
		case 0:
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(location.x - 100, location.y + 130));
			shot->SetShotType(eEnemy1);
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(location.x - 100, location.y - 130));
			shot->SetShotType(eEnemy1);
			atack_pattern = 1;
			break;
		case 1:
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(location.x, location.y));
			shot->SetShotType(eEnemy1);
			atack_pattern = 2;
			break;
		case 2:
			object_manager->CreateGameObject<Enemy3>(Vector2D(location.x + 100, location.y + 180));
			object_manager->CreateGameObject<Enemy3>(Vector2D(location.x + 100, location.y - 180));
			atack_pattern = 0;
			break;
		default:
			break;
		}

		//タイマーリセット
		shot_timer = 0.0f;
	}

	//死
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

void Boss1::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	if (image != -1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
		DrawRotaGraphF(location.x + 50, location.y, 1.0f, π / 2, images[0], TRUE);
		DrawRotaGraphF(location.x, location.y, 2.75f, π / 2, images[1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


}

void Boss1::Finalize()
{
}

void Boss1::OnHitCollision(GameObject* hit_object)
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
		if(hp <= 0)
		{
			PlaySoundMem(bomb_sound[0], DX_PLAYTYPE_BACK, TRUE);
			PlaySoundMem(bomb_sound[1], DX_PLAYTYPE_BACK, TRUE);
			PlaySoundMem(bomb_sound[2], DX_PLAYTYPE_BACK, TRUE);
			PlaySoundMem(bomb_sound[3], DX_PLAYTYPE_BACK, TRUE);
		}
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}
}

void Boss1::Movement(float delta_seconds)
{
	float speed = 200.0f;

	if (location.x >= 1100)
	{
		velocity.x = -1.0f;
	}
	else
	{
		velocity.x = 0.0f;
	}

	location += velocity * speed * delta_seconds;
}

void Boss1::Animation()
{
}

int Boss1::GetBoss1Hp()
{
	return ratio;
}

float Boss1::GetBoss1DeathCount()
{
	return death_count;
}

bool Boss1::GetDeathFlag()
{
	return death_flag;
}