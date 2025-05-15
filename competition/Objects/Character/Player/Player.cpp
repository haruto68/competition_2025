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

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 座標
	location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);
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

}

Player::~Player()
{

}

void Player::Initialize()
{
	//画像読み込み
	image = LoadGraph("Resource/Images/player/player.png");
}

void Player::Update(float delta_seconds)
{
	Movement(delta_seconds);

	Animation();

	// 無敵状態の更新
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

	//入力機能インスタンス取得
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
	DrawFormatString(5, 50, GetColor(255, 255, 255), "現在のプレイヤーレベル：%d", player_stats.player_level);
	DrawFormatString(5, 70, GetColor(255, 255, 255), "累積プレイヤーレベル：%d", player_stats.current_exp);
	DrawFormatString(5, 90, GetColor(255, 255, 255), "次のレベルアップに必要なEXP：%d", player_stats.next_level_exp);
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
	// 移動スピード
	float speed = 200.0 + player_stats.move_speed;
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
		direction.y = -1.0f;
		flip_flag = FALSE;
	}
	if (leftstick.y < -0.5f || input->GetKey(KEY_INPUT_DOWN) || input->GetKey(KEY_INPUT_S))	//下移動
	{
		direction.y = 1.0f;
		flip_flag = FALSE;
	}
	if (leftstick.x < -0.5f || input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A))	//左移動
	{
		direction.x = -1.0f;
		flip_flag = FALSE;
	}
	if (leftstick.x > 0.5f || input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D))	//右移動
	{
		direction.x = 1.0f;
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


	//左画面端
	if ((location.x + velocity.x) < (collision.box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
	}
	//右画面端
	if ((location.x + velocity.x) >= (D_WIN_MAX_X) - (collision.box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
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


	//位置座標を加速度分減らす
	location += velocity * speed * delta_seconds;
}

void Player::Animation()
{

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
		if(player_stats.life_count < player_stats.player_hp_max)
		player_stats.life_count += 1.0f;		// HP残量アップ
		break;
	case ePowerUp::eDamage:
		player_stats.attack_power += 1.0f;		// 攻撃力アップ
		break;
	case ePowerUp::eSpeed:
		player_stats.move_speed = Max(100.0f, player_stats.move_speed + 5.0f);		// 移動速度アップ
		break;
	case ePowerUp::eShotspeed:
		SHOT_INTERVAL = Max(0.1f, SHOT_INTERVAL - 0.02f);  // 下限を0.02秒に制限
		break;
	case ePowerUp::eThreeway:
		threeway_flag = true;
	default:
		break;
	}
}