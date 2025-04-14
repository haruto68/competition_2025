#include"EnemyShot.h"
#include"../../../Utility/InputManager.h"

EnemyShot::EnemyShot()
{

	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// 座標
	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(10, 10);
	collision.object_type = eObjectType::ePlayerShot;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;

}

EnemyShot::~EnemyShot()
{

}

void EnemyShot::Initialize()
{

}

void EnemyShot::Update(float delta_seconds)
{
	Movement(delta_seconds);

	Animation();
}

void EnemyShot::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	__super::Draw(0.0f, this->flip_flag);


	switch (shot_type)
	{
	case ePlayer1:
		break;
	case ePlayer2:
		break;
	case ePlayer3:
		break;
	case eEnemy1:
		DrawBox(location.x - 5, location.y - 5, location.x + 5, location.y + 5, GetColor(150, 0, 0), TRUE);
		break;
	case eEnemy2:
		DrawBox(location.x - 5, location.y - 5, location.x + 5, location.y + 5, GetColor(0, 150, 0), TRUE);
		break;
	case eEnemy3:
		DrawBox(location.x - 5, location.y - 5, location.x + 5, location.y + 5, GetColor(0, 0, 150), TRUE);
		break;
	default:
		break;
	}
}

void EnemyShot::Finalize()
{

}

void EnemyShot::OnHitCollision(GameObject* hit_object)
{

}

Vector2D EnemyShot::GetScreenVelocity()
{
	Vector2D value = 0.0f;
	value.x = screen_velocity;
	screen_velocity = 0.0f;
	return value;
}

Vector2D EnemyShot::GetVelocity()
{
	return this->velocity;
}

void EnemyShot::SetVelocity(Vector2D velocity)
{
	this->velocity += velocity;
}

void EnemyShot::Movement(float delta_seconds)
{
	// 移動スピード
	float speed = 200.0f;
	// 移動方向
	Vector2D direction = 0.0f;


	switch (shot_type)
	{
	case ePlayer1:
		break;
	case ePlayer2:
		break;
	case ePlayer3:
		break;
	case eEnemy1:
		velocity.x = -1.0f;
		break;
	case eEnemy2:
		DrawBox(location.x - 5, location.y - 5, location.x + 5, location.y + 5, GetColor(0, 150, 0), TRUE);
		break;
	case eEnemy3:
		DrawBox(location.x - 5, location.y - 5, location.x + 5, location.y + 5, GetColor(0, 0, 150), TRUE);
		break;
	default:
		break;
	}

	
	//位置座標を加速度分減らす
	location += velocity * speed * delta_seconds;

}

void EnemyShot::Animation()
{

}