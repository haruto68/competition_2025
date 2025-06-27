#include "Boss3.h"

Boss3::Boss3() :
	images(),
	atack_interval(0.0f),
	shot_timer_2(0.0f),
	shot_cooldown_2(0.0f),
	shot_timer_3(0.0f),
	shot_cooldown_3(0.0f),
	shot_wave(0),
	shot_wave_y(0),
	wave_change_count(0.0f)
{
	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(150, 200);						//当たり判定の大きさ
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
	max_hp = 2000;
	hp = float(max_hp);

	//画像読み込み
	image = rm->GetImages("Resource/Images/enemy/ship3_col3.png")[0];

	images[0] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/Enemy_Tank_Base.png")[0];
	images[1] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip3_Base.png")[0];
	images[2] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip3_Base_Tilt1.png")[0];
	images[3] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip3_Base_Tilt2.png")[0];
	images[4] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip3_Upgraded.png")[0];
	images[5] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip3_Upgraded_Tilt1.png")[0];
	images[6] = rm->GetImages("Resource/Images/GameMaker/Enemies/Ship/EnemyShip3_Upgraded_Tilt2.png")[0];

	image = images[1];

	exp_num = 0;
}

Boss3::~Boss3()
{
}

void Boss3::Initialize()
{
	atack_pattern = 0;
	atack_interval = 0.6f;

	shot_cooldown_2 = 0.25f;
	shot_cooldown_3 = 0.375f;
	shot_cooldown_3 = 0.375f;

	shot_wave_y = 380;

	ChangeVolumeSoundMem(bomb_sound_volume[0], bomb_sound[0]);
	ChangeVolumeSoundMem(bomb_sound_volume[1], bomb_sound[1]);
	ChangeVolumeSoundMem(bomb_sound_volume[2], bomb_sound[2]);
	ChangeVolumeSoundMem(bomb_sound_volume[3], bomb_sound[3]);
}

void Boss3::Update(float delta_seconds)
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
	shot_timer_3 += delta_seconds;

	EnemyShot* shot;

	//基本攻撃
	if (hp > 0 && shot_timer >= atack_interval)
	{
		switch (atack_pattern)
		{
			//レーザー攻撃
		case 0:
			break;
		case 3:
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1280 + 640, location.y));
			shot->SetShotType(eEnemy15);
			atack_pattern = 4;
			break;
		case 7:
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1280 + 640, location.y));
			shot->SetShotType(eEnemy15);
			atack_pattern = 8;
			break;
		case 12:
			//突進攻撃へ
			atack_pattern = 99;
			atack_interval = 2.0f;
			break;

			//突進
		case 99:
			atack_pattern = 100;
			atack_interval = 3.0f;
			break;
		case 100:
			break;
		case 101:
			atack_interval = 2.0f;
			atack_pattern += 1;
			break;
		case 102:
			break;
		case 103:
			atack_interval = 0.6f;
			atack_pattern = 200;
			break;

		//雑魚敵
		case 200:
			//object_manager->CreateGameObject<Enemy10>(Vector2D(1280 + 40, location.y + 200));
			//object_manager->CreateGameObject<Enemy10>(Vector2D(1280 + 40, location.y - 200));
			atack_pattern += 1;
			atack_interval = 0.2f;
			break;
		case 201:
			object_manager->CreateGameObject<Enemy11>(Vector2D(1280 + 40, 380 - 200));
			atack_pattern += 1;
			break;
		case 202:
			object_manager->CreateGameObject<Enemy11>(Vector2D(1280 + 40, 380 - 150));
			atack_pattern += 1;
			break;
		case 203:
			object_manager->CreateGameObject<Enemy11>(Vector2D(1280 + 40, 380 - 100));
			atack_pattern += 1;
			break;
		case 204:
			object_manager->CreateGameObject<Enemy11>(Vector2D(1280 + 40, 380 - 50));
			atack_pattern += 1;
			break;
		case 205:
			object_manager->CreateGameObject<Enemy11>(Vector2D(1280 + 40, 380));
			atack_pattern += 1;
			break;
		case 206:
			object_manager->CreateGameObject<Enemy11>(Vector2D(1280 + 40, 380 + 50));
			atack_pattern += 1;
			break;
		case 207:
			object_manager->CreateGameObject<Enemy11>(Vector2D(1280 + 40, 380 + 100));
			atack_pattern += 1;
			break;
		case 208:
			object_manager->CreateGameObject<Enemy11>(Vector2D(1280 + 40, 380 + 150));
			atack_pattern += 1;
			break;
		case 209:
			object_manager->CreateGameObject<Enemy11>(Vector2D(1280 + 40, 380 + 200));
			atack_pattern += 1;
			break;
		case 210:
			//レーザー攻撃へ
			atack_interval = 0.6f;
			atack_pattern = 1;
			break;

		default:
			atack_pattern += 1;
			break;
		}

		//タイマーリセット
		shot_timer = 0.0f;
	}


	//突進攻撃後戻りながら攻撃
	if (atack_pattern == 102)
	{
		shot_timer_2 += delta_seconds;

		if (hp > 0 && shot_timer_2 >= shot_cooldown_2)
		{
			shot_timer_2 = 0.0f;

			shot = object_manager->CreateGameObject<EnemyShot>(location);
			shot->SetShotType(eEnemy2);
			shot = object_manager->CreateGameObject<EnemyShot>(location);
			shot->SetShotType(eEnemy3);
		}

	}


	//HPが8割以下でウェーブ攻撃
	if (hp > 0 && ratio <= 80 && shot_timer_3 >= shot_cooldown_3)
	{
		if(ratio > 40)//HPが4割以上
		{
			shot_cooldown_3 = 0.6f;
			shot_timer_3 = 0.0f;

			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1280 + 40, shot_wave_y - 250));
			shot->SetShotType(eEnemy17);
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1280 + 40, shot_wave_y + 250));
			shot->SetShotType(eEnemy17);

			int w = 0;
			w = 35;
			switch (shot_wave)
			{
			case 0:
				shot_wave_y += w;
				break;
			case 1:
				shot_wave_y -= w;
				break;
			}
			if (shot_wave_y == 380 + w * 4)
			{
				shot_wave = 1;
			}
			if (shot_wave_y == 380 - w * 4)
			{
				shot_wave = 0;
			}
		}
		else if(wave_change_count < 7)
		{
			wave_change_count += delta_seconds;
			shot_wave_y = 380;
		}
		else
		{
			shot_cooldown_3 = 0.3f;
			shot_timer_3 = 0.0f;

			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1280 + 40, shot_wave_y - 250));
			shot->SetShotType(eEnemy18);
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1280 + 40, shot_wave_y + 250));
			shot->SetShotType(eEnemy18);

			int w = 0;
			w = 75;
			switch (shot_wave)
			{
			case 0:
				shot_wave_y += w;
				break;
			case 1:
				shot_wave_y -= w;
				break;
			}
			if (shot_wave_y == 380 + w * 4)
			{
				shot_wave = 1;
			}
			if (shot_wave_y == 380 - w * 4)
			{
				shot_wave = 0;
			}
		}
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

void Boss3::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	if(ratio > 0)
	{
		//予測線
		if (atack_pattern == 99 || atack_pattern == 101)
		{
			int upper_left_x = 0;
			int upper_left_y = location.y - collision.box_size.y / 2;
			int lower_right_x = 1280;
			int lower_right_y = location.y + collision.box_size.y / 2;

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
			DrawBox(upper_left_x, upper_left_y, lower_right_x, lower_right_y, GetColor(255, 0, 0), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	//
	if (image != -1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
		DrawRotaGraphF(location.x + 50, location.y, 1.0f, π / 2, images[0], TRUE);
		//DrawRotaGraphF(location.x, location.y, 2.35f, π / 2, images[1], TRUE);
		DrawRotaGraphF(location.x, location.y, 2.35f, π / 2, image, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
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
		if (hp <= 0)
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

void Boss3::Movement(float delta_seconds)
{
	float speed = 200.0f;

	if (atack_pattern == 0)//登場時のみ
	{
		if (location.x >= 1150)
		{
			velocity.x = -1.0f;
		}
		else
		{
			velocity.x = 0.0f;
			velocity.y = 0.7f;
			atack_pattern = 1;
		}
	}
	else//登場時以降
	{
		//上下
		if ((location.y + velocity.y) <= (65.0f + collision.box_size.y) || (location.y + velocity.y) >= (680 - collision.box_size.y))
		{

			if (velocity.y < 0)
				velocity.y = 0.7f;
			else
				velocity.y = -0.7f;
		}
		if (location.y <= (65.0f + collision.box_size.y))
		{
			velocity.y = 1.0f;
		}
		if (location.y >= (680 - collision.box_size.y))
		{
			velocity.y = -1.0f;
		}
		

		if (atack_pattern == 99)
		{
			//プレイヤーY座標追跡
			velocity.y = Tracking(location, Vector2D(location.x, player_location.y)).y * 0.7;
			//velocity.y = 0.0f;
			velocity.x = 2.0f;
			if (image == images[1] && ratio <= 50)
			{
				image = images[4];
			}
		}
		if(atack_pattern == 100)
		{
			velocity.y = 0.0f;
			velocity.x -= 0.125f;
			if (location.x < -300.0f)
			{
				velocity.x = 0.0f;
				atack_pattern = 101;
			}
		}

		if (atack_pattern == 101)
		{
			velocity.y = 0.0f;
		}
		if (atack_pattern == 102)
		{
			velocity.y = 0.0f;
			velocity.x = 2.5f;
			if (location.x > 1150.0f)
			{
				velocity.x = 0.0f;
				velocity.y = 0.7f;
				atack_pattern = 103;
			}
		}
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