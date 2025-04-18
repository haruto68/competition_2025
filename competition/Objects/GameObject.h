#pragma once

#include"Collision.h"


class GameObject
{
protected:
	Vector2D location;				//���W
	Collision collision;			//�R���W����
	int image;						//�摜
	unsigned char z_layer;			//���C���[
	bool is_mobility;				//����
	Vector2D player_location;		//�v���C���[���W
	Vector2D old_player_location;	//�������v���C���[���W

public:
	GameObject();
	~GameObject();

public:
	virtual void Initialize();
	virtual void Update(float);
	virtual void Draw(const Vector2D&, bool) const;
	virtual void Finalize();

	virtual void OnHitCollision(GameObject*);	//�����蔻��ʒm����
	const Vector2D& GetLocation() const;		//���W�擾����
	void SetLocation(const Vector2D);			//���W�ݒ菈��
	const Collision& GetCollision() const;		//�R���W�����擾����
	const unsigned char GetZLayer() const;		//���C���[�擾����
	const bool GetMobility() const;				//�����擾����

	void SetPlayerLocation(Vector2D location);	//�v���C���[���W�ݒ菈��
	Vector2D Tracking(Vector2D A, Vector2D B);	//A��B��ǔ����鏈��

};