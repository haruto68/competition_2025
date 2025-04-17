#include "Enemy3.h"

Enemy3::Enemy3() : box_size(0.0f)
{
}

Enemy3::~Enemy3()
{
}

void Enemy3::Initialize()
{
	box_size = Vector2D(150.0f, 50.0f);
	speed = 200.0f;
}

void Enemy3::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();
}

void Enemy3::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	// ‰¼(”’‚¢ŽlŠp‚ð•`‰æ‚·‚é)
	Vector2D t1 = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);
	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 255, 255), TRUE);
	DrawString(t1.x, t1.y, "Enemy3", GetColor(0, 0, 0), TRUE);
}

void Enemy3::Finalize()
{
	
}

void Enemy3::OnHitCollision(GameObject*)
{
}

void Enemy3::Movement(float delta_seconds)
{
	location.x -= 1.0f * speed * delta_seconds;
	if (location.x <= 640 || location.x >= 1280)
	{
		speed *= -1;

	}
}

void Enemy3::Animation()
{
}
