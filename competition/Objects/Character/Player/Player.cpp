#include"Player.h"
#include"../../../Utility/InputManager.h"
#include"UserTemplate.h"


Player::Player() : 
	screen_velocity(0.0f),
	shot_timer(0.0f),
	SHOT_INTERVAL(0.1f)
{

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 座標
	location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);
	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(20, 20);
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
	
}

void Player::Update(float delta_seconds)
{
	Movement(delta_seconds);

	Animation();

	if (shot_timer > 0.0f)
	{
		shot_timer -= delta_seconds;
	}

	//入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	if (CheckHitKey(KEY_INPUT_B) && shot_timer <= 0.0f)
	{
		PlayerShot* shot = object_manager->CreateGameObject<PlayerShot>(this->location);
		shot->SetShotType(ePlayer1);
		shot->SetPlayerStats(this->GetPlayerStats());
		shot_timer = SHOT_INTERVAL;
	}
	if (input->GetButtonDown(KEY_INPUT_C))
	{
		
	}
}

void Player::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);

	DrawBox(location.x - 10, location.y - 10, location.x + 10, location.y + 10, GetColor(255, 0, 0), TRUE);
}

void Player::Finalize()
{

}

void Player::OnHitCollision(GameObject* hit_object)
{

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
	float speed = 200.0f;
	// 移動方向
	Vector2D direction = 0.0f;
	// 減速
	float slow = 0.005f;

	// 入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();


	//入力状態によって移動方向を変更する
	if (input->GetKey(KEY_INPUT_UP) || input->GetKey(KEY_INPUT_W))		//上移動
	{
		direction.y = -1.0f;
		flip_flag = FALSE;
	}
	if (input->GetKey(KEY_INPUT_DOWN) || input->GetKey(KEY_INPUT_S))	//下移動
	{
		direction.y = 1.0f;
		flip_flag = FALSE;
	}
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A))	//左移動
	{
		direction.x = -1.0f;
		flip_flag = FALSE;
	}
	if (input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D))	//右移動
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
	if ((location.y + velocity.y) < (collision.box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
	}
	//下画面端
	if ((location.y + velocity.y) >= (D_WIN_MAX_Y)-(collision.box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
	}


	//位置座標を加速度分減らす
	location += velocity * speed * delta_seconds;
}

void Player::Animation()
{

}