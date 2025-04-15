#include "Enemy1.h"

Enemy1::Enemy1() : box_size(0.0f)
{

}

Enemy1::~Enemy1()
{

}


void Enemy1::Initialize()
{
	box_size = Vector2D(150.0f, 50.0f);
	speed = 200.0f;
}

void Enemy1::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

}

void Enemy1::Draw(const Vector2D& screeen_offset, bool file_flag) const
{
	// ‰¼(”’‚¢ŽlŠp‚ð•`‰æ‚·‚é)
	Vector2D t1 = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);
	DrawBoxAA(t1.x, t1.y, br.x, br.y, GetColor(255, 255, 255), TRUE);
	DrawString(t1.x, t1.y, "Enemy1", GetColor(0, 0, 0), TRUE);
}

void Enemy1::Finalize()
{

}

void Enemy1::OnHitCollision(GameObject* hit_object)
{

}

void Enemy1::Movement(float delta_seconds)
{
	/*float speed = 200.0f;*/
	//location.y -= 1.0f * speed * delta_seconds;
	location.y -= 1.0f*speed*delta_seconds;
	if (location.y <= 0||location.y>=720)
	{
		speed *= -1;
		
	}
}

void Enemy1::Animation()
{

}