#include "Boss3.h"

Boss3::Boss3() :
	images(),
	atack_interval(0.0f),
	shot_timer_2(0.0f),
	shot_cooldown_2(0.0f)
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
	max_hp = 10000;
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
}

Boss3::~Boss3()
{
}

void Boss3::Initialize()
{
	atack_pattern = 0;
	atack_interval = 0.6f;

	shot_cooldown_2 = 0.25f;
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


	EnemyShot* shot;

	//攻撃
	if (hp > 0 && shot_timer >= atack_interval)
	{
		switch (atack_pattern)
		{
		case 0:
			break;
		case 3:
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1280 + 640, location.y));
			shot->SetShotType(eEnemy15);
			atack_pattern = 5;
			break;
		case 7:
			shot = object_manager->CreateGameObject<EnemyShot>(Vector2D(1280 + 640, location.y));
			shot->SetShotType(eEnemy15);
			atack_pattern = 9;
		case 11:
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
			atack_pattern = 1;
			break;
		default:
			atack_pattern += 1;
			break;
		}

		//タイマーリセット
		shot_timer = 0.0f;
	}



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
	//
	if (image != -1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
		DrawRotaGraphF(location.x + 50, location.y, 1.0f, π / 2, images[0], TRUE);
		DrawRotaGraphF(location.x, location.y, 2.35f, π / 2, images[1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}



	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	// 現在のHPのバーの描画
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

		//プレイヤーY座標追跡
		//velocity.y = Tracking(location, Vector2D(location.x, player_location.y)).y * 0.7;
		

		if (atack_pattern == 99)
		{
			//プレイヤーY座標追跡
			velocity.y = Tracking(location, Vector2D(location.x, player_location.y)).y * 0.7;
			//velocity.y = 0.0f;
			velocity.x = 2.0f;
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