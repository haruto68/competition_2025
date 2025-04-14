#include "Enemy1.h"

Enemy1::Enemy1() 
{

}

Enemy1::~Enemy1()
{

}


void Enemy1::Initialize()
{

}

void Enemy1::Update(float delta_seconds)
{
	Movement(delta_seconds);
	Animation();

}

void Enemy1::Draw(const Vector2D& screeen_offset, bool file_flag) const
{

}

void Enemy1::Finalize()
{

}

void Enemy1::OnHitCollision(GameObject* hit_object)
{

}

void Enemy1::Movement(float delta_seconds)
{
	float speed = 100.0f;
	location.x -= 1.0f * speed * delta_seconds;
}

void Enemy1::Animation()
{

}