#include "Enemy2.h"

Enemy2::Enemy2() : box_size(0.0f), speed(200.0f)
{
}

Enemy2::~Enemy2()
{
}

void Enemy2::Initialize()
{
	//　仮敵2のサイズ(大きさ)
	box_size = Vector2D(100.0f, 100.0f);
	// 仮テキの速さ
	speed = 200.0f;
}

void Enemy2::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();
}

void Enemy2::Draw(const Vector2D&, bool) const
{
	// 仮(白い四角を描画する)
	Vector2D t1 = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);
	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 255, 255), TRUE);
	SetFontSize(15);
	DrawString(location.x,location.y, "Enemy2", GetColor(0, 0, 0), TRUE);
}

void Enemy2::Finalize()
{
}

void Enemy2::OnHitCollision(GameObject*)
{
}

void Enemy2::Movement(float delta_seconds)
{
	/*float speed = 200.0f;*/
//location.y -= 1.0f * speed * delta_seconds;
	location.y -= 1.0f * speed * delta_seconds;
	if (location.y <= 0 || location.y >= 720)
	{
		speed *= -1;

	}

}

void Enemy2::Animation()
{
}
