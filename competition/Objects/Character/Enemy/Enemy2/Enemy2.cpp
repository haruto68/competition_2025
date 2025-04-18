#include "Enemy2.h"

Enemy2::Enemy2() : speed(200.0f), bounce(800)
{
}

Enemy2::~Enemy2()
{
}

void Enemy2::Initialize()
{
	//　仮敵2のサイズ(大きさ)
	collision.box_size = Vector2D(20.0f, 20.0f);
	//box_size = Vector2D(20.0f, 20.0f);
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
	Vector2D t1 = location - (collision.box_size / 2.0f);
	Vector2D br = location + (collision.box_size / 2.0f);
	// 青色の四角を描画
	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(0, 255, 255), TRUE);
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
	velocity.x = -0.5f;
	bounce++;

	if (bounce > 800)
	{
		bounce = 0;
		if (velocity.y <= 0)
		{
			velocity.y = 0.5f;
		}
		else
		{
			velocity.y = -0.5f;
		}
	}

	location += velocity * speed * delta_seconds;
}

void Enemy2::Animation()
{
}
