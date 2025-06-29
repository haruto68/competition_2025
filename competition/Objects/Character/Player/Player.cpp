#include"Player.h"
#include"../../../Utility/InputManager.h"
#include"UserTemplate.h"


Player::Player() : 
	screen_velocity(0.0f),
	shot_timer(0.0f),
	SHOT_INTERVAL(0.3f),
	is_invincible(false),
	invincible_timer(0.0f),
	drone(nullptr),
	old_location(),
	soundseffect(),
	is_dead(false),
	blink_timer(0.0f),
	is_visible(true),
	blink_interval(0.1f),
	death_timer(0.0f),
	death_image_index(0),
	death_image_count(9),
	death_animation_interval(0.175f),
	death_animation_finished(false),
	animation_timer(0.0f),
	animation_frame_index(8),
	animation_interval(0.1f)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 座標
	location = Vector2D(D_WIN_MAX_X - 1080, D_WIN_MAX_Y / 2);
	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(35, 40);
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eEnemyShot);
	collision.hit_object_type.push_back(eObjectType::eItem);
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;

	soundseffect[0] = rm->GetSounds("Resource/Sounds/SoundsEffect/Player/PlayerShot.mp3");
	soundseffect[1] = rm->GetSounds("Resource/Sounds/SoundsEffect/Player/PlayerDamege.mp3");
	soundseffect[2] = rm->GetSounds("Resource/Sounds/SoundsEffect/Player/Player_dead.mp3");
	soundseffect[3] = rm->GetSounds("Resource/Sounds/SoundsEffect/Player/Exp_get.mp3");
	ChangeVolumeSoundMem(150, soundseffect[0]);
	ChangeVolumeSoundMem(200, soundseffect[1]);
	ChangeVolumeSoundMem(200, soundseffect[2]);
	ChangeVolumeSoundMem(100, soundseffect[3]);

	//画像読み込み
	normal_image = rm->GetImages("Resource/Images/player/Enemy Vehicles/Big Enemy 1/spr_plane_enemy_big_4.png", 12, 4, 3, 32, 32);
	dead_image = rm->GetImages("Resource/Images/player/Player_death_image.png", 9, 3, 3, 32, 30);

	if (dead_image[0] == 0)
	{
		DxLib_End();
	}

	image = normal_image[8];
}

void Player::Update(float delta_seconds)
{
	Movement(delta_seconds);

	Animation(delta_seconds);

	// 無敵状態の更新
	if (is_invincible == true)
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

	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	if ((InputManager::GetInstance()->GetButton(13) || CheckHitKey(KEY_INPUT_B)) && shot_timer <= 0.0f && is_dead == false)
	{
		PlayerShot* shot = object_manager->CreateGameObject<PlayerShot>(this->location);
		shot->SetShotType(ePlayer1);
		shot->SetPlayerStats(this->GetPlayerStats());

		if (player_stats.threeway_flag == true)
		{
			PlayerShot* angled_shot_up = object_manager->CreateGameObject<PlayerShot>(this->location);
			angled_shot_up->SetShotType(ePlayer1);
			angled_shot_up->SetPlayerStats(this->GetPlayerStats());
			angled_shot_up->SetAngle(10.0f);

			//PlayerShot* angled_shot_up2 = object_manager->CreateGameObject<PlayerShot>(this->location);
			//angled_shot_up2->SetShotType(ePlayer1);
			//angled_shot_up2->SetPlayerStats(this->GetPlayerStats());
			//angled_shot_up2->SetAngle(20.0f);

			PlayerShot* angled_shot_down = object_manager->CreateGameObject<PlayerShot>(this->location);
			angled_shot_down->SetShotType(ePlayer1);
			angled_shot_down->SetPlayerStats(this->GetPlayerStats());
			angled_shot_down->SetAngle(-10.0f);

			//PlayerShot* angled_shot_down2 = object_manager->CreateGameObject<PlayerShot>(this->location);
			//angled_shot_down2->SetShotType(ePlayer1);
			//angled_shot_down2->SetPlayerStats(this->GetPlayerStats());
			//angled_shot_down2->SetAngle(-20.0f);
		}

		PlaySoundMem(soundseffect[0], DX_PLAYTYPE_BACK, TRUE);
		shot_timer = SHOT_INTERVAL;
		player_stats.shot_speed = SHOT_INTERVAL;
	}
	if (drone == nullptr && player_stats.drone_hp > 0)
	{
		if (player_stats.drone_flag == true)
		{
			drone = object_manager->CreateGameObject<Drone>(this->location);
			drone->SetPlayerStats(&this->player_stats);
		}
		player_stats.drone_flag = false;
	}
	if (drone != nullptr && player_stats.drone_hp <= 0)
	{
		object_manager->DestroyGameObject(drone);
		drone = nullptr;
	}
}

void Player::Draw(const Vector2D& screen_offset, bool flip_flag) const
{

	if (is_visible == true && is_dead == false)
	{
		if (image != -1)
		{
			DrawRotaGraphF(location.x, location.y, 2.0f, π/2, image, TRUE);
		}

	}
	else if (is_dead == true)
	{
		if (image != -1 && death_image_index > 0)
		{
			DrawRotaGraphF(location.x, location.y, 2.0f, 0.0f, image, TRUE);
		}
	}
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
		if (player_stats.life_count == 0)
		{
			image = dead_image[0];
			PlaySoundMem(soundseffect[2], DX_PLAYTYPE_BACK, TRUE);
		}
		else if (player_stats.life_count > 0)
		{
			PlaySoundMem(soundseffect[1], DX_PLAYTYPE_BACK, TRUE);
		}
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
		if (player_stats.life_count == 0)
		{
			PlaySoundMem(soundseffect[2], DX_PLAYTYPE_BACK, TRUE);
		}
		else if(player_stats.life_count > 0)
		{
			PlaySoundMem(soundseffect[1], DX_PLAYTYPE_BACK, TRUE);
		}
		break;
	case eItem:
		AddExperience(10);
		PlaySoundMem(soundseffect[3], DX_PLAYTYPE_BACK, TRUE);
		break;
	default:
		break;
	}
	//player_stats.life_count = 6.0f;//デバッグ用無敵
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
	// 移動スピード
	float speed = 200.0 + player_stats.move_speed;

	if (InputManager::GetInstance()->GetButton(9))
	{
		speed = 100.0f;
	}

	// 移動方向
	Vector2D direction = 0.0f;
	// 減速
	float slow = 0.005f;//滑る
	slow = 1.0f;//滑らない

	// 入力管理インスタンス取得
	InputManager* input = InputManager::GetInstance();
	Vector2D leftstick = InputManager::GetInstance()->GetLeftStick();

	//入力状態によって移動方向を変更する
	if (leftstick.y > 0.5f || input->GetKey(KEY_INPUT_UP) || input->GetKey(KEY_INPUT_W))		//上移動
	{
		if (is_dead == true)
		{
			direction.y = 0.0f;
		}
		else
		{
			direction.y = -1.0f;
		}
		flip_flag = FALSE;
	}
	if (leftstick.y < -0.5f || input->GetKey(KEY_INPUT_DOWN) || input->GetKey(KEY_INPUT_S))	//下移動
	{
		if (is_dead == true)
		{
			direction.y = 0.0f;
		}
		else
		{
			direction.y = 1.0f;
		}
		flip_flag = FALSE;
	}
	if (leftstick.x < -0.5f || input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A))	//左移動
	{
		if (is_dead == true)
		{
			direction.x = 0.0f;
		}
		else
		{
			direction.x = -1.0f;
		}
		flip_flag = FALSE;
	}
	if (leftstick.x > 0.5f || input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D))	//右移動
	{
		if (is_dead == true)
		{
			direction.x = 0.0f;
		}
		else
		{
			direction.x = 1.0f;
		}
		flip_flag = FALSE;
	}

	//移動方向によって、Y座標の移動量の加減を行う
	if (direction.y != 0.0f)
	{
		//最高速度を超えないようにする
		float max_speed = Abs<float>((5.0f * 0.5 * direction.y));
		velocity.y += 0.5 * direction.y;
		velocity.y = Min<float>(Max<float>(velocity.y, -max_speed), max_speed);
	}
	else
	{
		//減速する
		if (velocity.y < -1e-6f)		//-1e-6f = (0に限りなく近い負の値)
		{
			//上移動の減速
			float calc_speed = velocity.y + slow;
			velocity.y = Min<float>(calc_speed, 0.0f);
		}
		else if (velocity.y > 1e-6f)	//1e-6f = (0に限りなく近い正の値)
		{
			//下移動の減速
			float cale_spped = velocity.y - slow;
			velocity.y = Max<float>(cale_spped, 0.0f);
		}
	}
	//移動方向によって、X座標の移動量の加減を行う
	if (direction.x != 0.0f)
	{
		//最高速度を超えないようにする
		float max_speed = Abs<float>((5.0f * 0.5 * direction.x));
		velocity.x += 0.5 * direction.x;
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);
	}
	else
	{
		//減速する
		if (velocity.x < -1e-6f)		//-1e-6f = (0に限りなく近い負の値)
		{
			//上移動の減速
			float calc_speed = velocity.x + slow;
			velocity.x = Min<float>(calc_speed, 0.0f);
		}
		else if (velocity.x > 1e-6f)	//1e-6f = (0に限りなく近い正の値)
		{
			//下移動の減速
			float cale_spped = velocity.x - slow;
			velocity.x = Max<float>(cale_spped, 0.0f);
		}
	}



	//上画面端
	if ((location.y + velocity.y) < (120) - (collision.box_size.y / 2.0f))
	{
		if ((location.y + velocity.y) < location.y)
		{
			velocity.y = 0.0f;
		}
	}
	//下画面端
	if ((location.y + velocity.y) >= (680) - (collision.box_size.y / 2.0f))
	{
		if ((location.y + velocity.y) > location.y)
		{
			velocity.y = 0.0f;
		}
	}
	//左画面端
	if ((location.x + velocity.x) < (collision.box_size.x / 2.0f))
	{
		if ((location.x + velocity.x) < location.x)
		{
			velocity.x = 0.0f;
		}
	}
	//右画面端
	if ((location.x + velocity.x) >= (D_WIN_MAX_X) - (collision.box_size.x / 2.0f))
	{
		if ((location.x + velocity.x) > location.x)
		{
			velocity.x = 0.0f;
		}
	}

	Vector2D future_location = location;
	future_location += velocity * speed * delta_seconds;

	if (future_location.x != location.x || future_location.y != location.y)
	{
		for (int i = 19; i > 0; i--)
		{
			old_location[i] = old_location[i - 1];
		}
		old_location[0] = location;
		if(drone != nullptr)
		{
			drone->SetLocation(old_location[19]);
		}
	}

	location += velocity * speed * delta_seconds;
	//位置座標を加速度分減らす
}

void Player::Animation(float delta_seconds)
{
	InputManager* input = InputManager::GetInstance();
	Vector2D leftstick = InputManager::GetInstance()->GetLeftStick();

	if (is_dead == false)
	{
		animation_timer += delta_seconds;

		if (leftstick.y < -0.5f  || input->GetKey(KEY_INPUT_S))
		{
			// 下移動アニメーション
			if (animation_timer >= animation_interval)
			{
				animation_frame_index++;
				if (animation_frame_index > 3)
				{
					animation_frame_index = 0;
				}
				image = normal_image[animation_frame_index];
				animation_timer -= animation_interval;
			}
		}
		else if (leftstick.y > 0.5f || input->GetKey(KEY_INPUT_W))
		{
			// 上移動アニメーション
			if (animation_timer >= animation_interval)
			{
				animation_frame_index++;
				if (animation_frame_index > 7 || animation_frame_index < 4)
				{
					animation_frame_index = 4;
				}
				image = normal_image[animation_frame_index];
				animation_timer -= animation_interval;
			}
		}
		else
		{
			// アイドルアニメーション
			if (animation_timer >= animation_interval)
			{
				animation_frame_index++;
				if (animation_frame_index > 11 || animation_frame_index < 8)
				{
					animation_frame_index = 8;
				}
				image = normal_image[animation_frame_index];
				animation_timer -= animation_interval;
			}
		}
	}

	// 爆発アニメーションの更新

	if (player_stats.life_count <= 0)
	{
		is_dead =true;
		death_timer += delta_seconds;
		if (death_timer >= death_animation_interval)
		{
			death_image_index++;
			death_timer -= death_animation_interval;

			// アニメーション終了
			if (death_image_index >= death_image_count)
			{
				death_image_index = death_image_count - 1; // 最後の画像を維持
				death_animation_finished = true;         // アニメーション終了フラグを立てる

				//image = normal_image[0]; // アニメーション終了後に通常画像に戻す (必要に応じて)
			}
			else
			{
				image = dead_image[death_image_index]; // 現在の爆発画像を設定
			}
		}
	}
	else
	{
		// 無敵時間中の点滅処理
		if (is_invincible)
		{
			blink_timer += delta_seconds;

			if (blink_timer >= blink_interval)
			{
				is_visible = !is_visible;
				blink_timer -= blink_interval;
			}
		}
		else
		{
			// 無敵時間でない場合は、常に表示
			is_visible = true;
		}
	}
}
void Player::AddExperience(float exp)
{
	player_stats.current_exp += exp;

	// レベルアップチェック
	while (player_stats.current_exp >= player_stats.next_level_exp)
	{
		player_stats.current_exp -= player_stats.next_level_exp;
		LevelUp();
	}
}

void Player::LevelUp()
{	
	player_stats.player_level++;			//プレイヤーレベルアップ
	player_stats.next_level_exp += 50;		//次のレベルアップに必要な経験値量の増加
}

void Player::StatsUp(ePowerUp powerup)
{
	switch (powerup)
	{
	case ePowerUp::eHp:
		if (player_stats.life_count < player_stats.player_hp_max)
		{
			if (is_dead == false)
			{
				player_stats.life_count += 1.0f;		// HP残量アップ
			}
		}
		break;
	case ePowerUp::eDamage:
		player_stats.attack_power += 1.0f;		// 攻撃力アップ
		break;
	case ePowerUp::eSpeed:
		if (player_stats.move_speed >= 100.0f)
		{

		}
		else
		{
			player_stats.move_speed = player_stats.move_speed + 20.0f;
		}
		//player_stats.move_speed = Max(100.0f, player_stats.move_speed + 5.0f);		// 移動速度アップ
		break;
	case ePowerUp::eShotspeed:
		SHOT_INTERVAL = Max(0.1f, SHOT_INTERVAL - 0.02f);  // 下限を0.02秒に制限
		player_stats.shot_speed_cnt++;
		break;
	case ePowerUp::eThreeway:
		player_stats.threeway_flag = true;
		break;
	case ePowerUp::eShot_HitRange:
		player_stats.player_shot_hitrange_up = player_stats.player_shot_hitrange_up + 2.0f;
		break;
	case ePowerUp::eDrone:
		player_stats.drone_flag = true;
		player_stats.drone_hp +=1 ;
		player_stats.drone_count += 1;
		break;
	default:
		break;
	}
}