#include"DxLib.h"
#include"GameObject.h"
#include"GameObjectManager.h"

GameObject::GameObject() :
	location(0.0f),
	image(NULL),
	z_layer(0),
	is_mobility(false)
{

}

GameObject::~GameObject()
{

}

/// <summary>
/// ����������
/// </summary>
void GameObject::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void GameObject::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void GameObject::Draw(const Vector2D& screen_offset, bool flip_flag) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, image, TRUE, flip_flag);
}

/// <summary>
/// �I��������
/// </summary>
void GameObject::Finalize()
{

}

void GameObject::OnHitCollision(GameObject* hit_object)
{

}

const Vector2D& GameObject::GetLocation() const
{
	return location;
}

void GameObject::SetLocation(const Vector2D location)
{
	this->location = location;
}

const Collision& GameObject::GetCollision() const
{
	return collision;
}

const unsigned char GameObject::GetZLayer() const
{
	return z_layer;
}

const bool GameObject::GetMobility() const
{
	return is_mobility;
}