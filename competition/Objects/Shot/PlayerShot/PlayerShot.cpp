#include"PlayerShot.h"
#include"../../../Utility/InputManager.h"

PlayerShot::PlayerShot() :
	screen_velocity(0.0f),
	Color(),
	Shotmode()
{

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 座標
	location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);
	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(5, 5);
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

	ShotModeChange();
}

void PlayerShot::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);
	DrawBox(location.x - 2.5, location.y - 2.5, location.x + 2.5, location.y + 2.5, Color, TRUE);
}

void PlayerShot::Finalize()
{

}

void PlayerShot::OnHitCollision(GameObject* hit_object)
{
	//	if (hit_object == nullptr)
	//		return;

	//// 敵との衝突なら削除
	//if (hit_object->GetObjectType() == eObjectType::eEnemy)
	//{
	//	this->SetDestroy();
	//}
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
	float speed = 800.0f;
	// 移動方向
	float direction = 0.0f;

	switch (shot_type)
	{
	case ePlayer1:
		Color = GetColor(0, 255, 255);
		velocity.x = 1.0f;
		break;
	case ePlayer2:
		Color = GetColor(255, 0, 255);
		velocity.x += 0.00045f;
		break;
	case ePlayer3:
		Color = GetColor(200, 200, 200);
		velocity.x = 1.0f;
		break;
	}

	//位置座標を加速度分減らす
	location += velocity * speed * delta_seconds;
}

void PlayerShot::Animation()
{

}

void PlayerShot::ShotModeChange()
{

}