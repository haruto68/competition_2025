#include"PlayerShot.h"
#include"../../../Utility/InputManager.h"

PlayerShot::PlayerShot() :
	screen_velocity(0.0f)
{

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 座標
	location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);
	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(0, 0);
	collision.object_type = eObjectType::ePlayerShot;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;

}

PlayerShot::~PlayerShot()
{

}

void PlayerShot::Initialize()
{

}

void PlayerShot::Update(float delta_seconds)
{
	Movement(delta_seconds);

	Animation();
}

void PlayerShot::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);

	DrawBox(location.x - 15, location.y - 15, location.x + 15, location.y + 15, GetColor(0, 255, 255), TRUE);

}

void PlayerShot::Finalize()
{

}

void PlayerShot::OnHitCollision(GameObject* hit_object)
{

}

Vector2D PlayerShot::GetScreenVelocity()
{
	Vector2D value = 0.0f;
	value.x = screen_velocity;
	screen_velocity = 0.0f;
	return value;
}

Vector2D PlayerShot::GetVelocity()
{
	return this->velocity;
}

void PlayerShot::SetVelocity(Vector2D velocity)
{
	this->velocity += velocity;
}

void PlayerShot::Movement(float delta_seconds)
{
	// 移動スピード
	float speed = 200.0f;
	// 移動方向
	float direction = 0.0f;

	// 入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();

	//Gキーで弾を発射する
	if (input->GetKey(KEY_INPUT_G))
	{
		direction = 1.0f;
		flip_flag = FALSE;
	}

	//移動方向によって、X座標の移動量の加減を行う
	if (direction != 0.0f)
	{
		velocity.x += 0.5 * direction;
	}

	//位置座標を加速度分減らす
	while ((location.x + velocity.x) <= (D_WIN_MAX_X)-(collision.box_size.x / 2.0f))
	{
		location += velocity * speed * delta_seconds;
	}
}

void PlayerShot::Animation()
{

}