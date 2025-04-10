#pragma once

#include"Collision.h"

class GameObject
{
protected:
	Vector2D location;
	Collision collision;
	int image;
	unsigned char z_layer;
	bool is_mobility;

public:
	GameObject();
	~GameObject();

public:
	virtual void Initialize();
	virtual void Update(float);
	virtual void Draw(const Vector2D&, bool) const;
	virtual void Finalize();

	virtual void OnHitCollision(GameObject*);
	const Vector2D& GetLocation() const;
	void SetLocation(const Vector2D);
	const Collision& GetCollision() const;
	const unsigned char GetZLayer() const;
	const bool GetMobility() const;

};