#include"PlayerShot.h"
#include"../../../Utility/InputManager.h"

PlayerShot::PlayerShot() :
	screen_velocity(0.0f),
	Color(),
	attack_power(0.0f),
	Shotmode(),
	image_size(0.0f),
	hit_sound(0)
{

}

PlayerShot::~PlayerShot()
{

}

void PlayerShot::Initialize()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// コリジョン設定
	collision.is_blocking = true;
	collision.box_size = Vector2D(5 + player_stats.player_shot_hitrange_up, 5 + player_stats.player_shot_hitrange_up);
	collision.object_type = eObjectType::ePlayerShot;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	// 画像設定
	// レイヤー設定
	z_layer = 2;
	// 可動性設定
	is_mobility = true;

	bullet_image = rm->GetImages("Resource/Images/player/player_bullet.png", 1, 1, 1, 16, 16);
	image = bullet_image[0];

	hit_sound = rm->GetSounds("Resource/Sounds/SoundsEffect/Enemy/enemybreak.mp3");
	ChangeVolumeSoundMem(80, hit_sound);
}

void PlayerShot::Update(float delta_seconds)
{
	Movement(delta_seconds);

	Animation();

	ShotModeChange();
	image_size = 1.0f + player_stats.player_shot_hitrange_up / 5;
}

void PlayerShot::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	DrawRotaGraphF(location.x, location.y, image_size, 0.0, image, TRUE, this->flip_flag);
}

void PlayerShot::Finalize()
{

}

void PlayerShot::OnHitCollision(GameObject* hit_object)
{
	eObjectType type = hit_object->GetCollision().object_type;

	switch (type)
	{
	case eNone:
		break;
	case ePlayer:
		break;
	case eEnemy:
		object_manager->DestroyGameObject(this);
		PlaySoundMem(hit_sound, DX_PLAYTYPE_BACK, TRUE);
		break;
	case ePlayerShot:
		break;
	case eEnemyShot:
		break;
	case eItem:
		break;
	default:
		break;
	}
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

void PlayerShot::SetAngle(float degree)
{
    float radian = degree * (3.14f / 180.0f);
    this->velocity.x = cosf(radian);
    this->velocity.y = -sinf(radian); // y軸が下方向に正ならマイナス
}